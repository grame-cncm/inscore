
.PHONY: push

PACK  := build/INScore-$(VERSION).dmg
VPACK := INScore-$(VERSION)-$(ID).dmg

push:
	git config --global user.name 'INScore deployment'
	git config --global user.email 'fober@grame.fr'
	git checkout -t origin/$(BRANCH)
	mv $(PACK) $(VPACK)
	git add $(VPACK)
	git commit -am "Automated report"
	git push

