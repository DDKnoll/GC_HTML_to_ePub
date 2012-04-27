/*
 * zip_epub_procs_sh.h - header for zip_epub_procs_sh.c
 *  only contains public procedures
 */

#ifndef __zip_epub_procs_sh__
#define __zip_epub_procs_sh__

/* make_epub_container - creates a .epub file containing the META-INF folder 
 *  (with container.xml) and the mimetype file
 * given the name of the epub as a char * (without the .epub extension!)
 */
int make_epub_container(char *book_name);


/* as of April 25, is not working, so don't use until fixed!*/
/* add_folder_to_epub - adds given folder to epub zip
 * preconditions:
 *  file_name is the name of an existing file in the current working directory
 *  epub_name (without the .epub extension) is the name of an existing epub file
 */
int add_folder_to_epub(char *epub_name, char *folder_name);

#endif
