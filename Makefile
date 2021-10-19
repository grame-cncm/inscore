
.PHONY: package

package:
	echo $(ID) > inscore-$(ID).txt
	cat inscore-$(ID).txt


publish:
	git config --global user.name 'INScore deploy'
	git config --global user.email 'fober@grame.fr'
	git checkout -t origin/Julien
	git add inscore-$(ID).txt
	git commit -am "Automated report"
	git push

