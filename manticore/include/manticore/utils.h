//
//  utils.h
//  reton
//
//  Created by Luca on 18.02.21.
//

#include <stdint.h>
#include <util/kutils.h>

struct proc_cred {
    char posix_cred[0x100]; // HACK big enough
    kptr_t cr_label;
    kptr_t sandbox_slot;
};

struct manticore_mapped_file {
    void *ptr;
    int size;
}

#ifdef __cplusplus
extern "C" {
#endif

    bool patch_TF_PLATFORM(kptr_t task);
    void proc_set_root_cred(kptr_t proc, struct proc_cred * *old_cred);
    int perform_root_patches(kptr_t ucred);
    char *get_path_for_pid(pid_t pid);
    pid_t pid_of_process(const char *name);
    bool restartSpringBoard(void);
    int runCommandv(const char *cmd, int argc, const char *const *argv,
                    void (^unrestrict)(pid_t), bool wait, bool quiet);
    pid_t look_for_proc(const char *proc_name);
    pid_t look_for_proc_basename(const char *base_name);
    void patch_amfid(pid_t amfid_pid);
    bool setCSFlagsByPID(pid_t pid);
    void *CDHashFor(char *file);
    bool isSymlink(const char *filename);
    bool isDirectory(const char *filename);
    bool isMountpoint(const char *filename);
    bool deleteFile(const char *file);
    bool ensureDirectory(const char *directory, int owner, mode_t mode);
    bool ensureSymlink(const char *to, const char *from);
    bool ensureFile(const char *file, int owner, mode_t mode);
    int waitForFile(const char *filename);

    bool runningAsRoot();

    bool manticoreMmapFile(const char *const path,
                           struct manticore_mapped_file *file);
    void manticoreMunmapFile(struct manticore_mapped_file * file);

#ifndef arraySize
#define arraySize(x) ((sizeof x) / (sizeof *x))
#endif

/* todo: c++ templates */
#ifndef ptrSub
#define ptrSub(a, b) (void *)((unsigned long long)a - (unsigned long long)b)
#endif

#ifndef ptrAdd
#define ptrAdd(a, b) (void *)((unsigned long long)a + (unsigned long long)b)
#endif

#ifdef __cplusplus
}
#endif
