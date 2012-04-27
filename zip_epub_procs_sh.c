#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* 2 major parts:
 *  creates epub with META-INF folder, container.xml and mimetype
 *  has add_folder_to_epub which adds a given file (in current directory) to 
 *    the given epub - DOESN'T WORK YET! 
 */

/* preconditions for all!
 * in current working directory, these files/folders do not exist:
 *   mimetype
 *   META-INF/
 *  and that no existing .epub document has the same name as the one you're 
 *    trying to create.
 */

/* These shell commands are required:
 * zip
 * mkdir
 * chmod
 */

/* "main" files - will be accessable through zip_epub_procs.h
 */

/* make_epub_container - creates a .epub file containing the META-INF folder 
 *  (with container.xml) and the mimetype file
 * given the name of the epub as a char * (without the .epub extension!)
 */

int make_epub_container(char *book_name){
  //creates the mimefile and META-INF
  make_mime_file();
  make_meta_inf();

  //zips mimefile and META-INF into book_name.epub, then 
  char zip_cmd[200]; // commandline is about 32 chars, so book name < 170 chars
  sprintf(zip_cmd, "zip -rm %s%s %s %s", book_name, ".epub", "mimetype", "META-INF/");
  //sprintf(zip_cmd, "zip -r %s%s %s %s", book_name, ".epub", "mimetype");

  system(zip_cmd);
  
  //adds META-INF via add_folder_to_epub NOT YET WORKING (and only to test)
  //add_folder_to_epub(book_name, "META-INF/");
   return 1;
}

//DOESN'T WORK YET!!! dunno why
/* add_folder_to_epub - adds given folder to epub zip
 * preconditions:
 *  file_name is the name of an existing file in the current working directory
 *  epub_name (without the .epub extension) is the name of an existing epub file
 */

//qs: does folder_name need to have the final /?
int add_folder_to_epub(char *epub_name, char *folder_name){
  char zip_cmd[100];
  sprintf(zip_cmd, "zip add %s%s %s", epub_name, ".epub", folder_name);
  system(zip_cmd);

  return 1;
}


/*******************************************************************************
 * helper procedures
 */

/* make_mime_file - creates the mimetype file in current working directory
 */
int make_mime_file(){
 //creates and writes file in current directory
  FILE *mime_file = fopen("mimetype", "w");
  fprintf(mime_file, "application/epub+zip");
  fclose(mime_file);

  return 1;
}

/* make_meta_inf - creates META-INF folder and container.xml (inside META-INF)
 *  both are made in current working directory.
 */

int make_meta_inf(){
  //makes META-INF folder and sets permissions (rwx for all - I think)
  mkdir("META-INF");
  chmod("META-INF", 0777);

  //creates and writes container.xml file in META-INF folder
  FILE *container_file = fopen("META-INF/container.xml", "w");
  fprintf(container_file, "<?xml version='1.0' encoding='utf-8'?>\n<container xmlns=\"urn:oasis:names:tc:opendocument:xmlns:container\" version=\"1.0\">\n  <rootfiles>\n    <rootfile media-type=\"application/oebps-package+xml\" full-path=\"OEBPS/content.opf\"/>\n  </rootfiles>\n</container>");
  fclose(container_file);

  return 1;
}


/* temporary main - basic testing
 *
 */

int main(int argc, char *argv[]){
  printf("testint 123, before f'n call\n");

  if(argc < 2){
    printf("No name for the epub given.\n");
    return 0;
  }

  make_epub_container(argv[1]);
  printf("nobody died\n");
  return 1;
}
