(require 'ITL "./ITL.lisp")


(defun itl-demo-msg ()
  '(("/ITL/scene/*" "del")
    ("/ITL/scene/title" "set" "txt" "Interlude Score Viewer")
    ("/ITL/scene/title" "scale" 2.5)
    ("/ITL/scene/title" "y" -0.5)))

(defun clock-init-msg ()
  '(("/ITL/scene/clock"  "set" "txt" " ")
    ("/ITL/scene/clock" "scale" 3.0)
    ("/ITL/scene/clock" "color" 255 50 50 255)))


(defun time-msg (arg)
  (itlsend (list "/ITL/scene/clock" "set" "txt" (write-to-string arg)))
  (- arg 1))

(defun scale-msg (arg)
  (itlsend (list "/ITL/scene/title" "scale" arg))
  (+ arg 0.02))

(defun clock-task (arg)
  (itlsend '("/ITL/scene/car*" "clock"))
  T)

(defun itl-root-path ()
  (itlsend (list "/ITL" "rootPath" (rootpath))))

(defun demo ()
  (itlstart)
  (itlsend (itl-demo-msg))
  (itlsend (clock-init-msg))
  (timetask #'time-msg 5 1 5)
  (timetask #'scale-msg 2.5 0.022 2)
  (itl-root-path)
  (itlsend '("/ITL" "load" "sync.inscore"))
  (timetask #'clock-task T 0.025 20)
  (itlstop))

;(demo)
