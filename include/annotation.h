/**
 * @file annotation.h
 * @author Jim Lai (jim.lai@realtek.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// Reference: https://learn.microsoft.com/en-us/cpp/code-quality/understanding-sal?view=msvc-170
#define _In_        // Input to called function
                    // Data is passed to the called function, and is treated as read-only.
                    //
                    //
#define _Inout_     // Input to called function, and output to caller
                    // Usable data is passed into the function and potentially is modified.
                    //
                    //
                    //
#define _Out_       // Output to caller
                    // The caller only provides space for the called function to write to. The 
                    // called function writes data into that space.
                    //
                    //