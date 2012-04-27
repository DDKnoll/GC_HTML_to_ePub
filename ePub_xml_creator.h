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
 * 3. write_ncx(metadata *meta, spine *theSpine)
 * creates the ncx specifying the hierarchical table of contents.
 *
 * 4. write_all_xml(metadata *meta, manifest *theManifest, spine *theSpine)
 * Writes the .opf, .ncx, and container.xml files.
 *
 * credit for basic layout of creating xml document:
 * Lucas Brasilino <brasilino@recife.pe.gov.br>
 *
 */
#ifndef XML_CREATOR
#define XML_CREATOR

#include "manifest.h"
#include "metadata.h"
#include "spine.h"

/************************************************************
 * Creates the container.xml file necessary for an epub book.
 * 
 */
int write_container(char* opf_path);

/*************************************************************************
 * creates the opf file specifying the book's metadata and included files.
 */
int write_opf(metadata *meta, manifest *theManifest, spine *theSpine);

/************************************************************************
 * creates the ncx specifying the hierarchical table of contents.
 */
int write_ncx(metadata *meta, spine *theSpine);

/***********************************************************************
 * Writes the .opf, .ncx, and container.xml files.
 */
int write_all_xml(metadata *meta, manifest *theManifest, spine *theSpine);

#endif
