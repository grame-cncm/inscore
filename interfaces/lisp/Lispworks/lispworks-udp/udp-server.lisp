;;;; -*- Mode: Lisp -*-
;;;; $Id: udp-server.lisp 568 2008-10-08 08:00:27Z binghe $
;;;; UDP Server Support for LispWorks

(in-package :comm+)

(defvar *client-address* 0 "client address used in udp process function")
(defvar *client-port* 0 "client port used in udp process function")

(defun udp-server-loop (arguments socket fn max-buffer-size)
  (declare (type socket-datagram socket)
           (type list arguments)
           (ftype (function (sequence) sequence) fn))
  "Main loop for A iterate UDP Server, function type as we declared."
  (mp:ensure-process-cleanup `(udp-server-loop-cleanup ,socket))
  (let ((message (make-array max-buffer-size
                             :element-type '(unsigned-byte 8)
                             :initial-element 0
                             :allocation :static))
        (socket-fd (socket-datagram-socket socket)))
    (fli:with-dynamic-foreign-objects ((client-addr (:struct sockaddr_in))
                                       (len :int
                                            #-(or lispworks3 lispworks4 lispworks5.0)
                                            :initial-element
                                            (fli:size-of '(:struct sockaddr_in))))
      (fli:with-dynamic-lisp-array-pointer (ptr message :type '(:unsigned :byte))
        (loop (let ((n (%recvfrom socket-fd ptr max-buffer-size 0
                                  (fli:copy-pointer client-addr :type '(:struct sockaddr))
                                  len)))
                (when (plusp n)
                  (let ((*client-address*
                         (ntohl (fli:foreign-slot-value
                                 (fli:foreign-slot-value client-addr
                                                         'sin_addr
                                                         :object-type '(:struct sockaddr_in)
                                                         :type '(:struct in_addr)
                                                         :copy-foreign-object nil)
                                 's_addr
                                 :object-type '(:struct in_addr))))
                        (*client-port*
                         (ntohs (fli:foreign-slot-value client-addr
                                                        'sin_port
                                                        :object-type '(:struct sockaddr_in)
                                                        :type '(:unsigned :short)
                                                        :copy-foreign-object nil))))
                    (let ((reply-message (apply fn (cons (subseq message 0 n) arguments))))
                      (when reply-message ;; or we don't make a reply message
                        (let ((length-out (length reply-message)))
                          (replace message reply-message)
                          (%sendto socket-fd ptr length-out 0
                                   (fli:copy-pointer client-addr :type '(:struct sockaddr))
                                   (fli:dereference len)))))))))))))

(defun udp-server-loop-cleanup (process socket)
  (declare (type socket-datagram socket)
           (type mp:process process)
           (ignore process))
  (close-datagram socket))

(defun start-udp-server (&key (function #'identity) (arguments nil)
                              (announce nil)
                              address (service 0)
                              (process-name (format nil "~S UDP server" service))
                              (loop-time 1)
                              (max-buffer-size +max-udp-message-size+))
  "Something like START-UP-SERVER"
  (let* ((socket (open-udp-socket :local-address address
                                  :local-port service
                                  :read-timeout loop-time
                                  :errorp t))
         (socket-fd (socket-datagram-socket socket)))
    (announce-server-started announce socket-fd nil)
    (let ((process (mp:process-run-function process-name nil
                                            #'udp-server-loop
                                            arguments ; additional arguments for function
                                            socket function max-buffer-size)))
      (setf (getf (mp:process-plist process) 'socket) socket)
      process)))

(defun stop-udp-server (process &key wait)
  (let ((socket (getf (mp:process-plist process) 'socket)))
    (mp:process-kill process)
    (prog1 (zerop (close-datagram socket))
      (when wait
        (mp:process-wait "Wait until UDP server process be killed"
                         #'(lambda () (not (mp:process-alive-p process))))))))
