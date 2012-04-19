/* Dugan Knoll
 * CSC323 Software Design - Spring 2012
 *
 * Contains the function write_container(char* opf_path) which creates
 * the container.xml file necessary for an epub book.
 *
 * credit for basic layout of creating xml document:
 * Lucas Brasilino <brasilino@recife.pe.gov.br>
 */

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)

/*
 *To compile this file using gcc you can type
 *gcc `xml2-config --cflags --libs` -o tree2 tree2.c
 */

/* A simple example how to create DOM. Libxml2 automagically 
 * allocates the necessary amount of memory to it.
*/
int main(int argc, char **argv)
{
  write_container("OPS/content.opf");
  return 0;
}

int write_container(char* opf_path){
    xmlDocPtr doc = NULL;       /* document pointer */
    xmlNodePtr container = NULL, rootFiles = NULL, rootFile = NULL;/* node pointers */
    xmlDtdPtr dtd = NULL;       /* DTD pointer */
    char buff[256];
    int i, j;

    LIBXML_TEST_VERSION;

    /* 
     * Creates a new document, a node and set it container as the root node
     */
    doc = xmlNewDoc(BAD_CAST "1.0");
    container = xmlNewNode(NULL, BAD_CAST "container");
    xmlDocSetRootElement(doc, container);


    xmlNewProp(container, BAD_CAST "version", BAD_CAST "1.0");
    xmlNewProp(container, BAD_CAST "xmlns", BAD_CAST "urn:oasis:names:tc:opendocument:xmlns:container");


    /* 
     * xmlNewChild() creates a new node, which is "attached" as child node
     * of root_node node. 
     */
    rootFiles = xmlNewChild(container, NULL, BAD_CAST "rootfiles",
                BAD_CAST NULL);
    /* 
     * The same as above, but the new child node doesn't have a content 
     */
    rootFile = xmlNewChild(rootFiles, NULL, BAD_CAST "rootfile", NULL);
    xmlNewProp(rootFiles, BAD_CAST "full-path", BAD_CAST opf_path);
    xmlNewProp(rootFiles, BAD_CAST "media-type", BAD_CAST "application/oebps-package+xml");


    /* 
     * Dumping document to stdio or file
     */
    xmlSaveFormatFileEnc("container.xml", doc, "UTF-8", 1);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
    return(0);
}
#else
int main(void) {
    fprintf(stderr, "tree support not compiled in\n");
    exit(1);
}
#endif
