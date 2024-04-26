# Для запуска скрипта:
#   cmake -P animals.cmake

cmake_minimum_required(VERSION 3.10)

set(animals "cat;mouse;dog;elephant;tiger;lion;axolotl;hippo;squirrel;wolf;shark;whale;bee;sloth;sheep;giraffe;scorpion")

message("№1\n")

foreach(x IN LISTS animals)
    message(${x})
endforeach()


message("\n№2\n")
list(LENGTH animals len)
message(${len})


message("\n№3\n")
foreach(x IN LISTS animals)
    string(LENGTH x len_x)
    message(${len_x})
    if(len_x GREATER 4)
        message(${x})
    endif()
endforeach()

message("\n№4\n")
list(SORT animals)
foreach(x IN LISTS animals)
    message(${x})
endforeach()

