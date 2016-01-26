NAME=projetAstro
VTKPATHL=/usr/lib/vtk-5.8/
VTKPATHI=/usr/include/vtk-5.8/
VTKOPTIONS=-lvtkCommon -lvtkFiltering -lvtkImaging -lvtkGraphics -lvtkGenericFiltering -lvtkIO -lvtkRendering -lvtkVolumeRendering -lvtkHybrid -lvtkWidgets -lvtkInfovis -lvtkGeovis -lvtkViews -lvtkCharts
OPTIONS=-std=c++11 -I${VTKPATHI} -L${VTKPATHL} ${VTKOPTIONS} -Wno-deprecated

all: ${NAME}_clean

${NAME}_clean: ${NAME} clean

${NAME}: main.o
	g++ *.o -o ${NAME} ${OPTIONS}

main.o: main.cpp Euler.o Leapfrog.o Parser.o
	g++ -c main.cpp ${OPTIONS}

Parser.o:
	g++ -c Parser.cpp ${OPTIONS}

Universe.o: Universe.cpp Particule.o
	g++ -c Universe.cpp ${OPTIONS}

Particule.o: Particule.cpp
	g++ -c Particule.cpp ${OPTIONS}

Euler.o: Euler.cpp Universe.o
	g++ -c Euler.cpp ${OPTIONS}

Leapfrog.o: Leapfrog.cpp Universe.o
	g++ -c Leapfrog.cpp ${OPTIONS}

clean:
	rm -rf *.o
