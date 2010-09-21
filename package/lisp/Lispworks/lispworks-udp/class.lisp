;;;; -*- Mode: Lisp -*-
;;;; $Id: class.lisp 643 2008-11-20 05:21:49Z binghe $

(in-package :comm+)

(defclass socket-datagram ()
  ((open-p :type boolean
           :accessor socket-open-p
           :initform t)
   (socket :type integer
           :reader socket-datagram-socket
           :initarg :socket)
   ;;; following slots are taken from USOCKET project
   (wait-list
    :initform nil
    :accessor wait-list
    :documentation "WAIT-LIST the object is associated with.")
   (state
    :initform nil
    :accessor state
    :documentation "Per-socket return value for the `wait-for-input' function.

The value stored in this slot can be any of
 NIL          - not ready
 :READ        - ready to read
 :READ-WRITE  - ready to read and write
 :WRITE       - ready to write

The last two remain unused in the current version."))
  (:documentation "datagram socket class"))

(defclass inet-datagram (socket-datagram rtt-info-mixin)
  ())

(defclass unix-datagram (socket-datagram)
  ((local-pathname :type (or null string pathname)
                   :accessor unix-datagram-pathname
                   :initarg :pathname)))

(defun make-inet-datagram (socket-fd)
  (make-instance 'inet-datagram :socket socket-fd))

(defun make-unix-datagram (socket-fd &optional pathname)
  (make-instance 'unix-datagram
                 :socket socket-fd
                 :pathname pathname))

(defmethod close-datagram ((socket socket-datagram))
  (close-socket (socket-datagram-socket socket)))

(defmethod close-datagram :after ((socket socket-datagram))
  (setf (socket-open-p socket) nil))

(defmethod close-datagram :after ((socket unix-datagram))
  (ignore-errors
    (delete-file (unix-datagram-pathname socket))))

;; Register a special free action for closing datagram usocket when being GCed
(defun socket-special-free-action (object)
  (when (and (typep object 'socket-datagram)
             (socket-open-p object))
    (close-datagram object)))

(eval-when (:load-toplevel :execute)
  (hcl:add-special-free-action 'socket-special-free-action))

(defgeneric socket-receive-timeout (socket))
(defgeneric (setf socket-receive-timeout) (seconds socket))

(defmethod socket-receive-timeout ((socket socket-datagram))
  (socket-receive-timeout (socket-datagram-socket socket)))

(defmethod (setf socket-receive-timeout) (seconds (socket socket-datagram))
  (setf (socket-receive-timeout (socket-datagram-socket socket))
        seconds))

(defgeneric send-message (socket buffer &key))

(defgeneric receive-message (socket &key))
