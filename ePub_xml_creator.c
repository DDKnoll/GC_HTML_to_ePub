/* Dugan Knoll
 * CSC323 Software Design - Spring 2012
 *
 * Contains the functions necessary for creating the ePub xml files.
 *
 * 1. write_container()
 * creates the container.xml file necessary for an epub book.
 *
 * 2. write_opf(metadata *meta, manifest *theManifest, spine *theSpine)
 * creates the opf file specifying the book's metadata and included files.
 *
 * 3. write_ncx(metadata *meta, manifest *theManifest)
 * creates the ncx specifying the hierarchical table of contents.
 *
 * 4. write_all_xml(metadata *meta, manifest *theManifest, spine *theSpine)
 * Writes the .opf, .ncx, and container.xml files.
 *
 * credit for basic layout of creating xml document:
 * Lucas Brasilino <brasilino@recife.pe.gov.br>
 *
 * TO DO:
 * 1. Verify that we're filling the appropriate information in .opf metadata.
 * 2. Save files in appropriate directories.
 */

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdlib.h>
#include "process_input_file.h"
#include "manifest.h"

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)

/*
 * To compile this file run the following command:
 * gcc ePub_xml_creator.c -l xml2 -I /usr/include/libxml2/ -o container_xml_creator
 */

/* This main function simply calls the function to demonstrate how it operates.
 * 
*/


/************************************************************
 * Creates the container.xml file necessary for an epub book.
 * 
 */
int write_container(char *opf_path){
  xmlDocPtr doc = NULL;       /* document pointer */
  xmlNodePtr container = NULL, rootFiles = NULL, rootFile = NULL;/* node pointers */
  xmlDtdPtr dtd = NULL;       /* DTD pointer */
  
  LIBXML_TEST_VERSION;
  
  /* 
   * Creates a new document, a node and set it container as the root node
   */
  doc = xmlNewDoc(BAD_CAST "1.0");
  container = xmlNewNode(NULL, BAD_CAST "container");
  xmlDocSetRootElement(doc, container);
  
  // Add the xml doctype properties to the container node.
  xmlNewProp(container, BAD_CAST "version", BAD_CAST "1.0");
  xmlNewProp(container, BAD_CAST "xmlns", BAD_CAST "urn:oasis:names:tc:opendocument:xmlns:container");
  
  /* 
   * Create the rootFiles node which contains a single rootfile node.
   * the rootfile has the path to the .opf file.
   */
  rootFiles = xmlNewChild(container, NULL, BAD_CAST "rootfiles",
                          BAD_CAST NULL);
  rootFile = xmlNewChild(rootFiles, NULL, BAD_CAST "rootfile", NULL);
  xmlNewProp(rootFile, BAD_CAST "full-path", BAD_CAST opf_path);
  xmlNewProp(rootFile, BAD_CAST "media-type", BAD_CAST "application/oebps-package+xml");
  
  
  /* 
   * Write the container.xml file.
   */
  xmlSaveFormatFileEnc(opf_path, doc, "UTF-8", 1);
  
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
  // xmlMemoryDump();
  return(0);
}

/*************************************************************************
 * write_opf(metadata *meta, manifest *theManifest)
 * creates the opf file specifying the book's metadata, manifest, and spine.
 */
int write_opf(metadata *meta, manifest *theManifest, spine *theSpine){
  /* document pointer */
  xmlDocPtr doc = NULL;
  
  /* node pointers */
  xmlNodePtr packageNode = NULL, metadataNode = NULL, tempNode = NULL;
  xmlNodePtr manifestNode = NULL, spineNode = NULL, guideNode = NULL;
  xmlDtdPtr dtd = NULL;       /* DTD pointer */

  /* pointers to the current items in the manifest and the spine. */
  itemNode *currentItem;
  itemRefNode *currentItemRef;

  LIBXML_TEST_VERSION;

  /****
   * Creates a new document, a node and set it container as the root node
   */
  doc = xmlNewDoc(BAD_CAST "1.0");
  packageNode = xmlNewNode(NULL, BAD_CAST "container");
  xmlDocSetRootElement(doc, packageNode);
  
  // Add the xml doctype properties to the package node.
  xmlNewProp(packageNode, BAD_CAST "version", BAD_CAST "2.0");
  xmlNewProp(packageNode, BAD_CAST "xmlns", BAD_CAST "http://www.idpf.org/2007/opf");
  xmlNewProp(packageNode, BAD_CAST "unique-identifier", BAD_CAST "Book ID");//TO DO!!!!!!!
  
  /****
   * Create the metaData node which contains information about the book.
   */
  metadataNode = xmlNewChild(packageNode, NULL, BAD_CAST "metadata",
                          BAD_CAST NULL);
  xmlNewChild(metadataNode, NULL, BAD_CAST "dc:title", meta->title);
  xmlNewChild(metadataNode, NULL, BAD_CAST "dc:language", meta->language);

  tempNode = xmlNewChild(metadataNode, NULL, BAD_CAST "dc:identifier",
                         BAD_CAST meta->title);
  xmlNewProp(tempNode, BAD_CAST "id", BAD_CAST meta->identifier);//TO DO!!!!!!!

  tempNode = xmlNewChild(metadataNode, NULL, BAD_CAST "dc:creator", BAD_CAST meta->title);
  xmlNewProp(tempNode, BAD_CAST "opf:file-as", BAD_CAST meta->author);
  xmlNewProp(tempNode, BAD_CAST "opf:role", BAD_CAST "aut");
  
  /****
   * Create the manifest node and its children.
   */
  manifestNode = xmlNewChild(packageNode, NULL, BAD_CAST "manifest",NULL);

  currentItem = theManifest->first;
  while(currentItem != NULL){
    tempNode = xmlNewChild(manifestNode, NULL, BAD_CAST "item", NULL);
    xmlNewProp(tempNode, BAD_CAST "id", BAD_CAST currentItem->href);
    xmlNewProp(tempNode, BAD_CAST "href", BAD_CAST currentItem->href);
    currentItem = currentItem->next;
  }

  /****
   * Create the Spine node and its children.
   */
  spineNode = xmlNewChild(packageNode, NULL, BAD_CAST "spine",NULL);
  xmlNewProp(spineNode, BAD_CAST "toc", BAD_CAST theSpine->toc);

  currentItemRef = theSpine->first;
  while(currentItemRef != NULL){
    tempNode = xmlNewChild(spineNode, NULL, BAD_CAST "itemref", NULL);
    xmlNewProp(tempNode, BAD_CAST "idref", BAD_CAST currentItemRef->idref);
    currentItemRef = currentItemRef->next;
  }

  /****
   * Create the guide node and its children.
   */

  //guideNode = xmlNewChild(packageNode, NULL, BAD_CAST "guide",NULL);
  //
  // For now, we won't worry about creating the guide, since it is optional.
  

  
  /****
   * Write the content.opf file.
   */
  xmlSaveFormatFileEnc("./content.opf", doc, "UTF-8", 1);
  
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
  //  xmlMemoryDump();
  return(0);
}


/************************************************************************
 * 3. write_ncx(metadata *meta, manifest *theManifest)
 * creates the ncx specifying the hierarchical table of contents.
 */
int write_ncx(metadata *meta, spine *theSpine){
  /* document pointer */
  xmlDocPtr doc = NULL;
  
  /* node pointers */
  xmlNodePtr ncxNode = NULL, headNode = NULL, docTitleNode = NULL,  docAuthorNode = NULL;
  xmlNodePtr navMapNode = NULL, tempNode = NULL;
  xmlDtdPtr dtd = NULL;       /* DTD pointer */

  /* Current item in the spine */
  itemRefNode *currentItemRef;

  /* Used to keep track of the playOrder*/
  int playOrder;

  /* Used for converting playOrder to a string */
  char playOrderBuffer[10];

  LIBXML_TEST_VERSION;

  /****
   * Creates a new document, a node and set it container as the root node
   */
  doc = xmlNewDoc(BAD_CAST "1.0");
  ncxNode = xmlNewNode(NULL, BAD_CAST "container");
  xmlDocSetRootElement(doc, ncxNode);

  /****
   * Create the doctype definition.
   */
  dtd = xmlCreateIntSubset(doc, BAD_CAST "xcf", BAD_CAST "-//NISO//DTD ncx 2005-1//EN",
                           BAD_CAST "http://www.daisy.org/z3986/2005/ncx-2005-1.dtd");
  
  /****
   * Add the xml doctype properties to the package node.
   */
  xmlNewProp(ncxNode, BAD_CAST "version", BAD_CAST "2005-1");
  xmlNewProp(ncxNode, BAD_CAST "xml:lang", BAD_CAST meta->language);
  xmlNewProp(ncxNode, BAD_CAST "xmlns", BAD_CAST "http://www.daisy.org/z3986/2005/ncx/");
  
  /****
   * Create the head node which contains meta information.
   */
  headNode = xmlNewChild(ncxNode, NULL, BAD_CAST "head", NULL);
  tempNode = xmlNewChild(headNode, NULL, BAD_CAST "dtb:uid", NULL);
  xmlNewProp(tempNode, BAD_CAST "content", BAD_CAST meta->identifier);
  tempNode = xmlNewChild(headNode, NULL, BAD_CAST "dtb:depth", NULL);
  xmlNewProp(tempNode, BAD_CAST "content", BAD_CAST "1");
  tempNode = xmlNewChild(headNode, NULL, BAD_CAST "dtb:totalPageCount", NULL);
  xmlNewProp(tempNode, BAD_CAST "content", BAD_CAST "0");
  tempNode = xmlNewChild(headNode, NULL, BAD_CAST "dtb:maxPageNumber", NULL);
  xmlNewProp(tempNode, BAD_CAST "content", BAD_CAST "0");

  /****
   * Add the docTitle node and its child title node.
   */
  docTitleNode = xmlNewChild(ncxNode, NULL, BAD_CAST "docTitle", NULL);
  tempNode = xmlNewChild(docTitleNode, NULL, BAD_CAST "title", meta->title);
  

  /****
   * Create the navMap node and its children.
   */
  navMapNode = xmlNewChild(ncxNode, NULL, BAD_CAST "navMap",NULL);
  playOrder = 1;

  currentItemRef = theSpine->first;
  while(currentItemRef != NULL){
    tempNode = xmlNewChild(navMapNode, NULL, BAD_CAST "navPoint", NULL);
    xmlNewProp(tempNode, BAD_CAST "class", BAD_CAST "chapter");
    xmlNewProp(tempNode, BAD_CAST "id", BAD_CAST currentItemRef->idref);
    sprintf(playOrderBuffer,"%d",playOrder);
    xmlNewProp(tempNode, BAD_CAST "playOrder", BAD_CAST playOrderBuffer);
    tempNode = xmlNewChild(tempNode, NULL, BAD_CAST "navLabel", NULL);
    xmlNewChild(tempNode, NULL, BAD_CAST "text", BAD_CAST currentItemRef->idref);
    tempNode = xmlNewChild(tempNode, NULL, BAD_CAST "content", NULL);
    xmlNewProp(tempNode, BAD_CAST "src", BAD_CAST currentItemRef->idref);
    //Note: idref must contain the filepath

    // Update the loop iteration and spine pointer
    currentItemRef = currentItemRef->next;
    playOrder += 1;
  }
  
  /* 
   * Write the table of contents .ncx file.
   */
  xmlSaveFormatFileEnc("./toc.ncx", doc, "UTF-8", 1);
  
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
  // xmlMemoryDump();
  return(1);
}

/***********************************************************************
 * 4. write_all_xml(metadata *meta, manifest *theManifest)
 * Writes the .opf, .ncx, and container.xml files.
 */
int write_all_xml(metadata *meta, manifest *theManifest, spine *theSpine){
  write_container("./container.xml");
  write_opf(meta, theManifest, theSpine);
  write_ncx(meta, theSpine);
  return(1);
}


#endif
