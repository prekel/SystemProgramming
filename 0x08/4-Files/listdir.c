/*! \file    listdir.c
 *  \brief   Directory reading demo.
 *
 *  \details List files in a directory via system calls.
 */
#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*   */
/*! \brief Get string with the type of the file
 *
 *  \details Get a string that describes the type of the file system entry.
 *
 *  \param   path     File system path.
 *
 *  \return           The type of the file with path.
 */
const char* GetFileType(const char* path)
{
  struct stat st;
  lstat(path, &st);
  if (S_ISLNK(st.st_mode))
    return "symbolic link";
  else if (S_ISDIR(st.st_mode))
    return "directory";
  else if (S_ISCHR(st.st_mode))
    return "character device";
  else if (S_ISBLK(st.st_mode))
    return "block device";
  else if (S_ISFIFO(st.st_mode))
    return "fifo";
  else if (S_ISSOCK(st.st_mode))
    return "socket";
  else if (S_ISREG(st.st_mode))
    return "regular file";
  else
    /* Unexpected.  Each entry should be one of the types above.  */
    assert(0);
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main(int argc, char* argv[])
{
  char* dirPath;
  DIR* dir;
  struct dirent* entry;
  char entryPath[PATH_MAX + 1];
  size_t pathLen;

  if (argc >= 2)
    /* If a directory was specified on the command line, use it.  */
    dirPath = argv[1];
  else 
    /* Otherwise, use the current directory.  */
    dirPath = ".";
    
  /* Copy the directory path into entry_path.  */
  strncpy(entryPath, dirPath, sizeof (entryPath));
  pathLen = strlen(dirPath);

  /* If the directory path doesn't end with a slash, append a slash.  */
  if (entryPath[pathLen - 1] != '/')
  {
    entryPath[pathLen] = '/';
    entryPath[pathLen + 1] = '\0';
    ++pathLen;
  }

  /* Start the listing operation of the directory specified on the
     command line.  */
  dir = opendir(dirPath);

  /* Loop over all directory entries.  */
  while ((entry = readdir(dir)) != NULL)
  {
    const char* type;

    /* Build the path to the directory entry by appending the entry
       name to the path name.  */
    strncpy(entryPath + pathLen, entry->d_name,
	     sizeof (entryPath) - pathLen);

    /* Determine the type of the entry.  */
    type = GetFileType(entryPath);

    /* Print the type and path of the entry.  */
    printf("%-18s: %s\n", type, entryPath);
  }

  /* All done.  */
  closedir(dir);
  return 0;
}
