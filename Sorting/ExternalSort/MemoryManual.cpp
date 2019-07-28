#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <errno.h>
#include <vector>

using namespace std;

#define MB_TO_BYTE (1024 * 1024)


void process_mem_usage(double &vm_usage, double &resident_set)
{
    vm_usage = 0.0;
    resident_set = 0.0;

    // the two fields we want
    unsigned long vsize;
    long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >>
            ignore >> ignore >> ignore >> ignore >> ignore >>
            ignore >> ignore >> ignore >> ignore >> ignore >>
            ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / MB_TO_BYTE;
    resident_set = rss * page_size_kb;
}

/**
 * MEMORY INFOR: 
 *              vim /proc/meminfo
 * 
 *      MemTotal:        7135732 kB
 *      MemFree:         3282840 kB
 *      MemAvailable:    5914500 kB
 *      Buffers:           16352 kB
 *      Cached:          2888432 kB
 *      SwapCached:            0 kB
 *      Active:          1134944 kB
 *      Inactive:        2548624 kB
 *      Active(anon):     756640 kB
 *      Inactive(anon):   109360 kB
 *      .........
 */


void checkMemoryInfo()
{
    std::ifstream ifs("/proc/meminfo", std::ios_base::in);
    std::string ignore;
    unsigned long long totalMem;
    unsigned long long freeMem;
    unsigned long long avalMem;

    ifs >> ignore >> totalMem >> ignore >> ignore >> freeMem >> ignore >> ignore >> avalMem;
    ifs.close();

    std::cout << "Total Mem = " << totalMem << std::endl;
    std::cout << "Free Mem = " << freeMem << std::endl;
    std::cout << "Aval Mem = " << avalMem << std::endl;
}


/****************************************************************************************************************
 * LINK: http://nadeausoftware.com/articles/2012/09/c_c_tip_how_get_physical_memory_size_system
 * On Linux, the /proc pseudo-file system includes several pseudo-files filled with system configuration information. 
 * /proc/meminfo contains detailed information about memory use.
        
    // struct sysinfo
    // {
    //     long uptime;                                  /* Seconds since boot */
    //     unsigned long loads[3];                       /* 1, 5, and 15 minute load averages */
    //     unsigned long totalram;                       /* Total usable main memory size */
    //     unsigned long freeram;                        /* Available memory size */
    //     unsigned long sharedram;                      /* Amount of shared memory */
    //     unsigned long bufferram;                      /* Memory used by buffers */
    //     unsigned long totalswap;                      /* Total swap space size */
    //     unsigned long freeswap;                       /* swap space still available */
    //     unsigned short procs;                         /* Number of current processes */
    //     unsigned long totalhigh;                      /* Total high memory size */
    //     unsigned long freehigh;                       /* Available high memory size */
    //     unsigned int mem_unit;                        /* Memory unit size in bytes */
    //     char _f[20 - 2 * sizeof(long) - sizeof(int)]; /* Padding for libc5 */
    // };

 /**************************************************************************************************************/

unsigned long long getSystemInfo()
{
    struct sysinfo myinfo;
    unsigned long total_bytes;
    unsigned long usage_mem;
    unsigned long free_mem;
    sysinfo(&myinfo);

    total_bytes = myinfo.totalram * myinfo.mem_unit;
    free_mem = myinfo.freeram * myinfo.mem_unit;

    cout << "Total usable main memory size  = " << (myinfo.totalram * myinfo.mem_unit)  / MB_TO_BYTE << endl;
    cout << "Available memory size          = " << (myinfo.freeram * myinfo.mem_unit)   / MB_TO_BYTE << endl;
    cout << "Amount of shared memory        = " << (myinfo.sharedram * myinfo.mem_unit) / MB_TO_BYTE << endl;
    cout << "Memory used by buffers         = " << (myinfo.bufferram * myinfo.mem_unit) / MB_TO_BYTE << endl;
    cout << "Total swap space size          = " << (myinfo.totalswap * myinfo.mem_unit) / MB_TO_BYTE << endl;
    cout << "Total high memory size         = " << (myinfo.totalhigh * myinfo.mem_unit) / MB_TO_BYTE << endl;
    cout << "Available high memory size     = " << (myinfo.freehigh * myinfo.mem_unit)  / MB_TO_BYTE << endl;
    cout << "Memory unit size in bytes      = " << (myinfo.mem_unit) << endl;

    // printf("total usable main memory is %lu B, %lu MB\n", total_bytes, total_bytes / 1024 / 1024);

    return total_bytes;
}

void dropCache()
{
    sync();

    std::ofstream ofs("/proc/sys/vm/drop_caches");
    ofs << "3" << std::endl;
    ofs.close();
}

int main()
{
    using std::cout;
    using std::endl;
    static int counter = 0;
    double vm, rss;

    process_mem_usage(vm, rss);
    cout << "VM: " << vm << "; RSS: " << rss << endl;

    checkMemoryInfo();

    getSystemInfo();

    return 0;
}