#ifndef VFS_H
#define VFS_H

typedef enum inode_type_e{
    INODE_FILE,
    INODE_DIRECTORY
}inode_type_e;

typedef struct inode_t{
    inode_type_e type;

} inode_t;
void vfs_init();

void vfs_create_directory();

#endif
