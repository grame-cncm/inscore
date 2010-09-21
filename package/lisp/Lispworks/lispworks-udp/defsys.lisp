;;;; -*- Mode: Lisp -*-
;;;; $Id: defsys.lisp 643 2008-11-20 05:21:49Z binghe $
;;;; System Definition for LispWorks UDP

(in-package :cl-user)

;;; Load COMM package
(require "comm")

#+(and lispworks4 win32)
(pushnew :mswindows *features*)

(defsystem lispworks-udp
  (:optimize ((safety 3) (debug 3)))
  :members (package
            rtt
            lispworks-udp
            class
            wait-for-input
	    condition
            udp-client
            udp-server
            rtt-client
            unix
            unix-server)
  :rules ((:in-order-to :compile :all
           (:requires (:load :previous)))))
