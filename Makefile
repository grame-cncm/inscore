
.PHONY: push

PACK  := build/INScore-$(VERSION).dmg
VPACK := INScore-$(VERSION)-$(ID).dmg

push:
	git config --global user.name 'INScore deployment'
	git config --global user.email 'dfober@gmail.com'
	git checkout -t origin/$(BRANCH)
	mv $(PACK) $(VPACK)
	git lfs track "*.dmg"
	git add .gitattributes
	git add $(VPACK)
	git commit -am "Automated report"
	git push

