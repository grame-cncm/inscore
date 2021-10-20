
.PHONY: package

package:
	echo $(ID) > inscore-$(ID).txt
	cat inscore-$(ID).txt


publish:
	git config --global user.name 'INScore deploy'
	git config --global user.email 'fober@grame.fr'
	git fetch
	git checkout -t origin/$(BRANCH)
	git add inscore-$(ID).txt
	git commit -am "Automated report"
	git push

