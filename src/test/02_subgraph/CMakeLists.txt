Ubpa_GetTargetName(core "${PROJECT_SOURCE_DIR}/src/core")
Ubpa_AddTarget(
  TEST
  MODE EXE
  INC "include"
  LIB ${core}
)
