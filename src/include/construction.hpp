///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This file creating the window or multiple windows     //
// for the user, without the need to messing around with //
// threads.                                              //
///////////////////////////////////////////////////////////

#ifndef CONSTRUCTION_HPP
#define CONSTRUCTION_HPP

#include "utils/utils.hpp"

#ifdef _WIN32
#include "windows/renderer.hpp"
#elif __linux__
#include "linux/renderer.hpp"
#endif

#include <thread>
#include <vector>
#include <memory>
#include <type_traits>

START_NAMESPACE

// This functions are creating multiple windows easily 
std::vector<std::thread> threads;

template<typename T>
void _GFX_construct_window() {}

template<typename T, typename U, typename... Args, 
    typename = typename std::enable_if<std::is_base_of<Renderer, U>::value>::type>
void _GFX_construct_window() 
{
    // Creates a thread for the window
    // with a default function
    std::thread th([]() ->
        void {
            U win;
            while(win.is_running())
                win.on_update();
        }
    );

    // Moving the thread to the threads vector
    threads.push_back(std::move(th));

    // Construct the next window
    _GFX_construct_window<T, Args...>();
}

template<typename... Args>
void construct_windows() 
{
    // Start constructing the windows
    _GFX_construct_window<void, Args...>();

    // Call all of the threads
    for(auto& th : threads)
        th.join();
}

END_NAMESPACE

#endif // CONSTRUCTION_HPP
