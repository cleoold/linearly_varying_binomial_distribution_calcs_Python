
all : install

install :
	python3 setup.py install || python setup.py install

debugging :
	bin/python3 setup.py build_ext --inplace

release :
	bin/python3 setup.py sdist bdist_wheel

update-submodule :
	git submodule foreach git pull origin master
