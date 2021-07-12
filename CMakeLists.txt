#==============================
# Requirements
#==============================

cmake_minimum_required(VERSION 3.10)

#==============================
# Project Settings
#==============================

if (NOT PROJECT_DECLARED)
    project("Gaia Behavior Tree" LANGUAGES CXX VERSION 0.9.1)
    set(PROJECT_DECLARED)
endif()

#==============================
# Project Modules
#==============================

add_subdirectory("GaiaBehaviorTree")

if (WITH_TEST)
    add_subdirectory("GaiaBehaviorTreeTest")
endif()