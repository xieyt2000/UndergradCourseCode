#!/bin/bash
${JAVA_HOME}/bin/java -cp build/:${PWD}/lib/joeq_core.jar:${PWD}/lib/jwutil.jar $@
