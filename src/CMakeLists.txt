
set(CMAKE_VERBOSE_MAKEFILE ON)
include(${QT_USE_FILE})

include_directories(${QT_QTSVG_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(qhanoi_src
    diskarea.cpp
    highscores.cpp
    highscorewindow.cpp
    main.cpp
    mainwindow.cpp
    playfield.cpp
)

qt4_wrap_cpp(qhanoi_moc
    diskarea.h
    highscorewindow.h
    mainwindow.h
    playfield.h
)

add_executable(qhanoi ${qhanoi_src} ${qhanoi_moc})

target_link_libraries(qhanoi ${QT_LIBRARIES} ${QT_QTSVG_LIBRARY})


