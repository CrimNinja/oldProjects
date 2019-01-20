// thread example
#include "concur2018.h"
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <chrono>
#include <math.h>

std::mutex mtx;           // mutex for critical section

using namespace std;
using namespace std::chrono;

// Summary of the multiple thread implementation.

// A total of 6 threads were used to replicate the behavior of the main function.
// The threads had data sent into them as separate batches so no two threads were working on
// one file at the same time. locks were used in the cout stream to remove discrepancies.


// Issues that were found.

// Race conditions and deadlocks.

// Solution - To make batches of the data when getting the fileslist and then giving the threads
// their own batch of data to work with instead of working with the main list. This eliminated the
// issue of having any deadlocks or race conditions as each thread has its own separate data to work
// with.

// Alternate solution - Use locks. However, using lesser locks was desired and therefore this was
// not implemented in the end run. Example of this lock mechanism is shown in the locking of the
// cout stream so that no two threads try to access this at the same time. Hence removing the random
// prints that were seen without the locks.

void convertFiles( std::string location ) {

    //
    std::cout << "Starting conversion of " << location << std::endl;

    // library provides us filelist:
    concur2018::FileList files = concur2018::GetFiles( location );

    // Select operation based on the first letter of filename.
    // We skip path parsing and just assume a fixed format:
    // "inputs/Filename.png"
    //  01234567
    // BUG: won't work if location != "inputs"
    const auto FIRSTLETTER = 7;

    for( auto filename : files ) {

        std::cout << "Processing: " << filename << std::endl;
        // select fileoperation based on the first letter of filename:
        switch( filename[FIRSTLETTER] ) {
        case 'C':
            concur2018::ProcessFile( filename, concur2018::Copyright );
            break;
        case 'R':
            concur2018::ProcessFile( filename, concur2018::Rotate );
            break;
        case 'B':
            concur2018::ProcessFile( filename, concur2018::Border );
            break;
        case 'G':
            concur2018::ProcessFile( filename, concur2018::Grayscale );
            break;
        case 'U':
            concur2018::ProcessFile( filename, concur2018::Unfocus );
            break;
        default:
            std::cerr << "Cannot operate with firstletter '" + std::string(1, filename[FIRSTLETTER]) + "'" << std::endl;
            break;
        } // switch
    } // for

    std::cout << "Ending conversion of " << location << std::endl;

}

void processFileThread(concur2018::FileList files)
{
//    mtx.lock();
    const auto FIRSTLETTER = 7;
//    std::cout << "hi " << endl;
    for (auto filename : files) {
        mtx.lock();
        std::cout << "Processing: " << filename << std::endl;
        mtx.unlock();
        switch( filename[FIRSTLETTER] ) {
        case 'C':
            concur2018::ProcessFile( filename, concur2018::Copyright );
            break;
        case 'R':
            concur2018::ProcessFile( filename, concur2018::Rotate );
            break;
        case 'B':
            concur2018::ProcessFile( filename, concur2018::Border );
            break;
        case 'G':
            concur2018::ProcessFile( filename, concur2018::Grayscale );
            break;
        case 'U':
            concur2018::ProcessFile( filename, concur2018::Unfocus );
            break;
        default:
            mtx.lock();
            std::cerr << "Cannot operate with firstletter '" + std::string(1, filename[FIRSTLETTER]) + "'" << std::endl;
            mtx.unlock();
            break;
        } // switch
    } // for
//    mtx.unlock();
}

void convertFilesThread(std::string location)
{
    std::cout << "Starting conversion of images with threads " << location << std::endl;

    // library provides us filelist:
    concur2018::FileList files = concur2018::GetFiles( location );

    const unsigned int numFiles = files.size();

    // Sending in the data as seperate batches eliminates the occurance of race conditions and allows for the threads
    // to continue their work without any discripancies from other threads.

    concur2018::FileList batch1 (files.begin(), files.begin() + floor(numFiles * 1/6) + 1);
    concur2018::FileList batch2 (files.begin() + floor(numFiles * 1/6) + 1,
                                     files.begin() + floor(numFiles * 2/6) + 1);
    concur2018::FileList batch3 (files.begin() + floor(numFiles * 2/6) + 1,
                                     files.begin() + floor(numFiles * 3/6) + 1);
    concur2018::FileList batch4 (files.begin() + floor(numFiles * 3/6) + 1,
                                     files.begin() + floor(numFiles * 4/6) + 1);
    concur2018::FileList batch5 (files.begin() + floor(numFiles * 4/6) + 1,
                                     files.begin() + floor(numFiles * 5/6) + 1);
    concur2018::FileList batch6 (files.begin() + floor(numFiles * 5/6) + 1, files.end());

    std::thread threads1 (processFileThread, batch1);
    std::thread threads2 (processFileThread, batch2);
    std::thread threads3 (processFileThread, batch3);
    std::thread threads4 (processFileThread, batch4);
    std::thread threads5 (processFileThread, batch5);
    std::thread threads6 (processFileThread, batch6);

    threads1.join();
    threads2.join();
    threads3.join();
    threads4.join();
    threads5.join();
    threads6.join();
}

int main()
{
//    auto start = high_resolution_clock::now();
    convertFilesThread("inputs"); // uses 6 threads to run the convertFiles function.
//    auto stop = high_resolution_clock::now();

//    auto duration_thread = duration_cast<microseconds>(stop - start);

//    cout << "Time taken by function thread: "
//         << duration_thread.count() << " microseconds" << endl;

////    auto start2 = high_resolution_clock::now();
//    convertFiles("inputs");
////    auto stop2 = high_resolution_clock::now();

////    auto duration_normal = duration_cast<microseconds>(stop2 - start2);

////    cout << "Time taken by function normal: "
////         << duration_normal.count() << " microseconds" << endl;

    return 0;
}
