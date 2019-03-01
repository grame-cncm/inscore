#
#
#

VERSION	 := $(shell cat ../../version.txt)
NAME     := inscore:$(VERSION)

build:
	@echo building docker image $(NAME)...
	docker build -t $(NAME) .

help:
	@echo "Makefile for docker image management."
	@echo "Available targets are:"
	@echo "  build (default) : build the docker image"
	@echo "  list    : list current docker images and containers"
	@echo "  run     : run the $(NAME) image"
	@echo "  rm      : remove the $(NAME) image"

list:
	docker images
	docker container ls

run:
	docker run -p 6000:6000 -t -i $(NAME) bash

rmstopped:
	@echo remove all stopped containers
	docker rm $(shell docker ps -a -q)

rm:
	docker rmi -f $(NAME)
