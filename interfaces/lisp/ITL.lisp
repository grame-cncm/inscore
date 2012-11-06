;------------------------------------------------------------------
; loading libraries
;------------------------------------------------------------------
(setf (logical-pathname-translations "ROOT")
  (list (list "**;*.*.*"
	(format () "~A**/*.*" 
	(namestring (make-pathname :device (pathname-device *load-pathname*)
	:directory (pathname-directory *load-pathname*)))))))


#+lispworks (load "root:Lispworks;asdf;asdf.lisp")
#+lispworks (load "root:Lispworks;lispworks-udp;lispworks-udp.asd")
#+lispworks (load "root:osc;osc.asd")
#+lispworks (asdf:operate 'asdf:load-op 'lispworks-udp)
#+lispworks (asdf:operate 'asdf:load-op 'osc)
#+lispworks (compile-file "root:Lispworks;oscoverudp.lisp")
#+lispworks (load "root:Lispworks;oscoverudp")

#+allegro (print "todo: allegro support...")


;------------------------------------------------------------------
; rootpath utilities
;------------------------------------------------------------------
(defun path-to-string (p &optional s)
  (if (null (cdr p))
    (concatenate 'string s "/" (car p) "/")
    (path-to-string (cdr p) (concatenate 'string s "/" (car p)))))

(defun rootpath ()
  (path-to-string (cdr
  	(pathname-directory (translate-logical-pathname  "root:")))))


;------------------------------------------------------------------
; interlude communication
;------------------------------------------------------------------

(defvar *itlout* nil)
(defvar *itlin* nil)
(defvar *itlerr* nil)
(defvar *itlopened* nil)

(defun receive-fun (message)
 (let ((msg (osc::decode-msg-or-bundle message)))
   (format *standard-output* "RECEIVED from Interlude : ~a~%" msg)
   nil))

(defun itlstart ()
  (if (not *itlopened*)
    (progn
      (setf *itlout* (osc::open-osc-out-stream "127.0.0.1" 7000))
      (handler-case
          (progn
            (setf *itlin*  (osc::start-osc-server "127.0.0.1" 7001 #'receive-fun))
            (setf *itlerr* (osc::start-osc-server "127.0.0.1" 7002 #'receive-fun)))
        (error () (print "OSC input is not available (probably busy with another application).")))
      (setf *itlopened* T))
    ))

(defun itlstop ()
  (if *itlopened*
      (progn
        (osc::close-osc-stream *itlout*)
        (when *itlin* (osc::stop-osc-server *itlin*))
        (when *itlerr* (osc::stop-osc-server *itlerr*))
        (setf *itlin* nil)
        (setf *itlerr* nil)
        (setf *itlopened* nil)
        )))

(defun itlsend (msg &optional (debug nil))
  (if (listp (car msg))
    (progn  (osc::write-osc-msg (car msg) *itlout*)
      (if (not (null (cdr msg))) 
          (itlsend (cdr msg))))
    (progn
      (if debug (print msg))
      (osc::write-osc-msg msg *itlout*))))

;------------------------------------------------------------------
; misc
;------------------------------------------------------------------
(defvar *itlproc* 1)
(defun _timetask (f args interval duration)
  (do (( end (+ (get-universal-time) duration)))
      ((> (get-universal-time) end))
    (progn 
      (sleep interval)
      (setq args (funcall f args)))))

(defun timetask (f args interval duration  &key procname background (priority 60) )
  (if (eq procname nil)
      (progn
        (setq procname (format nil "ITLProc~3,'0D" *itlproc*))
        (setq *itlproc* (+ *itlproc* 1))))
  (if background
     (mp:process-run-function procname (list ':priority priority) #'_timetask f args interval duration )
    (_timetask f args interval duration)))

