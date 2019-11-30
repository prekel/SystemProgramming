/*! \file    write_journal_entry.c
 *  \brief   Write buffered record to journal file.
 *
 *  \details Write buffered record to journal file.
 *           Sync buffer via fsync system call.
 */
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const char* g_JournalFilename = "journal.log";

/*! \brief Write buffered record to journal file.
 *
 *  \details Write buffered record to journal file.
 *           It is also sync the buffer.
 *
 *  \param entry   Record to log.
 *
 *  \par           It uses the global variable as journal filename.
 */
void WriteJournalEntry(char* entry)
{
  int fd = open(g_JournalFilename, O_WRONLY | O_CREAT | O_APPEND, 0660);
  write(fd, entry, strlen(entry));
  write(fd, "\n", 1);
  fsync(fd);
  close(fd);
}
