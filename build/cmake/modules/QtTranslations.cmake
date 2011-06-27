# Some FintQt4.cmake are outdated ....
MACRO(_QT4_ADD_TRANSLATION _qm_files)
  FOREACH (_current_FILE ${ARGN})
    GET_FILENAME_COMPONENT(_abs_FILE ${_current_FILE} ABSOLUTE)
    GET_FILENAME_COMPONENT(qm ${_abs_FILE} NAME_WE)
    GET_SOURCE_FILE_PROPERTY(output_location ${_abs_FILE} OUTPUT_LOCATION)
    IF(output_location)
      FILE(MAKE_DIRECTORY "${output_location}")
      SET(qm "${output_location}/${qm}.qm")
    ELSE(output_location)
      SET(qm "${CMAKE_CURRENT_BINARY_DIR}/${qm}.qm")
    ENDIF(output_location)
    
    ADD_CUSTOM_COMMAND(OUTPUT ${qm}
      COMMAND ${QT_LRELEASE_EXECUTABLE}
      ARGS ${_abs_FILE} -qm ${qm}
      DEPENDS ${_abs_FILE}
      )
    SET(${_qm_files} ${${_qm_files}} ${qm})
  ENDFOREACH (_current_FILE)
ENDMACRO(_QT4_ADD_TRANSLATION)
