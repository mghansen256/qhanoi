
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${QT_QTSVG_INCLUDE_DIR})

set(qhanoi_src
    diskarea.cpp
    highscores.cpp
    highscorewindow.cpp
    main.cpp
    mainwindow.cpp
    playfield.cpp
)

qt5_wrap_cpp(qhanoi_moc
    diskarea.h
    highscorewindow.h
    mainwindow.h
    playfield.h
)

qt5_add_resources(qhanoi_res main.qrc)

add_executable(qhanoi ${qhanoi_src} ${qhanoi_moc} ${qhanoi_res})

target_link_libraries(qhanoi Qt5::Widgets Qt5::Xml Qt5::Svg ${QT_LIBRARIES} ${QT_QTSVG_LIBRARY})


