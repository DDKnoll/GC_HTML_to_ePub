CC = /usr/bin/gcc
CFLAGS = -Wall -ggdb3
INCLUDE = manifest.o metadata.o spine.o ePub_xml_creator.o process_input_file.o debug.o

test_ePub_xml_creator : ePub_xml_creator.o process_input_file.o 
	${CC} test_ePub_xml_creator.c ${INCLUDE} -l xml2 -I /usr/include/libxml2/ -o test_ePub_xml_creator

process_input_file.o : manifest.o metadata.o spine.o
	${CC} process_input_file.c -c

ePub_xml_creator.o : manifest.o metadata.o spine.o
	${CC} ePub_xml_creator.c -l xml2 -I /usr/include/libxml2/ -c

manifest.o :
	${CC} manifest.c -c

metadata.o :
	${CC} metadata.c -c

spine.o : debug.o
	${CC} spine.c -c

debug.o :
	${CC} debug.c -c

test_metadata : test_metadata.c 
	${CC} ${OPTIONS} -o test_metadata test_metadata.c

test_process_input_file : test_process_input_file.c 
	${CC} ${OPTIONS} -o test_process_input_file test_process_input_file.c

test_manifest : test_manifest.c 
	${CC} ${OPTIONS} -o test_manifest test_manifest.c

test_spine : test_spine.c 
	${CC} ${OPTIONS} -o test_spine test_spine.c
clean:
	rm ${INCLUDE} test_process_input_file test_manifest test_spine test_metadata test_xml_ePub_creator
