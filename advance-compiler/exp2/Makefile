compile: clean
	mkdir build
	${JAVA_HOME}/bin/javac -Xlint:-options -source 1.8 -target 1.8 \
		-cp lib/joeq_core.jar:lib/jwutil.jar \
	  -sourcepath src -d build `find src -name "*.java"`

clean:
	rm -rf build/
