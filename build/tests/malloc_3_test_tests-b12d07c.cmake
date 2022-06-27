add_test( malloc_3.Sanity /home/student/Desktop/OS_HW4/build/tests/malloc_3_test Sanity  )
set_tests_properties( malloc_3.Sanity PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Check size]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Check size]==]  )
set_tests_properties( [==[malloc_3.Check size]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.0 size]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[0 size]==]  )
set_tests_properties( [==[malloc_3.0 size]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Max size]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Max size]==]  )
set_tests_properties( [==[malloc_3.Max size]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( malloc_3.free /home/student/Desktop/OS_HW4/build/tests/malloc_3_test free  )
set_tests_properties( malloc_3.free PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.free 2]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[free 2]==]  )
set_tests_properties( [==[malloc_3.free 2]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.free 3]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[free 3]==]  )
set_tests_properties( [==[malloc_3.free 3]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.free holes 1]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[free holes 1]==]  )
set_tests_properties( [==[malloc_3.free holes 1]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.free holes 2]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[free holes 2]==]  )
set_tests_properties( [==[malloc_3.free holes 2]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.free holes 3]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[free holes 3]==]  )
set_tests_properties( [==[malloc_3.free holes 3]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Wilderness available]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Wilderness available]==]  )
set_tests_properties( [==[malloc_3.Wilderness available]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Wilderness available pad]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Wilderness available pad]==]  )
set_tests_properties( [==[malloc_3.Wilderness available pad]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Large allocation]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Large allocation]==]  )
set_tests_properties( [==[malloc_3.Large allocation]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Large unaligned allocation]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Large unaligned allocation]==]  )
set_tests_properties( [==[malloc_3.Large unaligned allocation]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( malloc_3.Alignment /home/student/Desktop/OS_HW4/build/tests/malloc_3_test Alignment  )
set_tests_properties( malloc_3.Alignment PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Alignment unaligned base]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Alignment unaligned base]==]  )
set_tests_properties( [==[malloc_3.Alignment unaligned base]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Alignment MMAP]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Alignment MMAP]==]  )
set_tests_properties( [==[malloc_3.Alignment MMAP]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( malloc_3.Reuse /home/student/Desktop/OS_HW4/build/tests/malloc_3_test Reuse  )
set_tests_properties( malloc_3.Reuse PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Reuse two blocks]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Reuse two blocks]==]  )
set_tests_properties( [==[malloc_3.Reuse two blocks]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Reuse two blocks reverse]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Reuse two blocks reverse]==]  )
set_tests_properties( [==[malloc_3.Reuse two blocks reverse]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Reuse two blocks both]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Reuse two blocks both]==]  )
set_tests_properties( [==[malloc_3.Reuse two blocks both]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Reuse two blocks sizes small]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Reuse two blocks sizes small]==]  )
set_tests_properties( [==[malloc_3.Reuse two blocks sizes small]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Reuse two blocks sizes small reversed]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Reuse two blocks sizes small reversed]==]  )
set_tests_properties( [==[malloc_3.Reuse two blocks sizes small reversed]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Reuse two blocks sizes large]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Reuse two blocks sizes large]==]  )
set_tests_properties( [==[malloc_3.Reuse two blocks sizes large]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( malloc_3.scalloc /home/student/Desktop/OS_HW4/build/tests/malloc_3_test scalloc  )
set_tests_properties( malloc_3.scalloc PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.scalloc taint]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[scalloc taint]==]  )
set_tests_properties( [==[malloc_3.scalloc taint]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.scalloc 0 size]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[scalloc 0 size]==]  )
set_tests_properties( [==[malloc_3.scalloc 0 size]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.scalloc Max size num]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[scalloc Max size num]==]  )
set_tests_properties( [==[malloc_3.scalloc Max size num]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.scalloc Max size size]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[scalloc Max size size]==]  )
set_tests_properties( [==[malloc_3.scalloc Max size size]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.scalloc Max size both]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[scalloc Max size both]==]  )
set_tests_properties( [==[malloc_3.scalloc Max size both]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Split block]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Split block]==]  )
set_tests_properties( [==[malloc_3.Split block]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Split block under threshold]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Split block under threshold]==]  )
set_tests_properties( [==[malloc_3.Split block under threshold]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Split block threshold]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Split block threshold]==]  )
set_tests_properties( [==[malloc_3.Split block threshold]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Merge with prev block]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Merge with prev block]==]  )
set_tests_properties( [==[malloc_3.Merge with prev block]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Merge with prev block pad]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Merge with prev block pad]==]  )
set_tests_properties( [==[malloc_3.Merge with prev block pad]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Merge with next block]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Merge with next block]==]  )
set_tests_properties( [==[malloc_3.Merge with next block]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Merge with next block pad]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Merge with next block pad]==]  )
set_tests_properties( [==[malloc_3.Merge with next block pad]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Merge with both blocks]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Merge with both blocks]==]  )
set_tests_properties( [==[malloc_3.Merge with both blocks]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.Merge with both blocks pad]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[Merge with both blocks pad]==]  )
set_tests_properties( [==[malloc_3.Merge with both blocks pad]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( malloc_3.realloc /home/student/Desktop/OS_HW4/build/tests/malloc_3_test realloc  )
set_tests_properties( malloc_3.realloc PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.realloc shrink]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[realloc shrink]==]  )
set_tests_properties( [==[malloc_3.realloc shrink]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc Max size]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc Max size]==]  )
set_tests_properties( [==[malloc_3.srealloc Max size]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case a]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case a]==]  )
set_tests_properties( [==[malloc_3.srealloc case a]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case a split]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case a split]==]  )
set_tests_properties( [==[malloc_3.srealloc case a split]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case a mmap]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case a mmap]==]  )
set_tests_properties( [==[malloc_3.srealloc case a mmap]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case b]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case b]==]  )
set_tests_properties( [==[malloc_3.srealloc case b]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case b metadata]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case b metadata]==]  )
set_tests_properties( [==[malloc_3.srealloc case b metadata]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case b split]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case b split]==]  )
set_tests_properties( [==[malloc_3.srealloc case b split]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case b wilderness]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case b wilderness]==]  )
set_tests_properties( [==[malloc_3.srealloc case b wilderness]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case b wilderness 2]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case b wilderness 2]==]  )
set_tests_properties( [==[malloc_3.srealloc case b wilderness 2]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case c]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case c]==]  )
set_tests_properties( [==[malloc_3.srealloc case c]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case c 2]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case c 2]==]  )
set_tests_properties( [==[malloc_3.srealloc case c 2]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case d]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case d]==]  )
set_tests_properties( [==[malloc_3.srealloc case d]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case d metadata]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case d metadata]==]  )
set_tests_properties( [==[malloc_3.srealloc case d metadata]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case d split]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case d split]==]  )
set_tests_properties( [==[malloc_3.srealloc case d split]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case e]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case e]==]  )
set_tests_properties( [==[malloc_3.srealloc case e]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case e no pad]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case e no pad]==]  )
set_tests_properties( [==[malloc_3.srealloc case e no pad]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case e split]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case e split]==]  )
set_tests_properties( [==[malloc_3.srealloc case e split]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case fi]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case fi]==]  )
set_tests_properties( [==[malloc_3.srealloc case fi]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case fii]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case fii]==]  )
set_tests_properties( [==[malloc_3.srealloc case fii]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case g]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case g]==]  )
set_tests_properties( [==[malloc_3.srealloc case g]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
add_test( [==[malloc_3.srealloc case h]==] /home/student/Desktop/OS_HW4/build/tests/malloc_3_test [==[srealloc case h]==]  )
set_tests_properties( [==[malloc_3.srealloc case h]==] PROPERTIES WORKING_DIRECTORY /home/student/Desktop/OS_HW4/build/tests)
set( malloc_3_test_TESTS malloc_3.Sanity [==[malloc_3.Check size]==] [==[malloc_3.0 size]==] [==[malloc_3.Max size]==] malloc_3.free [==[malloc_3.free 2]==] [==[malloc_3.free 3]==] [==[malloc_3.free holes 1]==] [==[malloc_3.free holes 2]==] [==[malloc_3.free holes 3]==] [==[malloc_3.Wilderness available]==] [==[malloc_3.Wilderness available pad]==] [==[malloc_3.Large allocation]==] [==[malloc_3.Large unaligned allocation]==] malloc_3.Alignment [==[malloc_3.Alignment unaligned base]==] [==[malloc_3.Alignment MMAP]==] malloc_3.Reuse [==[malloc_3.Reuse two blocks]==] [==[malloc_3.Reuse two blocks reverse]==] [==[malloc_3.Reuse two blocks both]==] [==[malloc_3.Reuse two blocks sizes small]==] [==[malloc_3.Reuse two blocks sizes small reversed]==] [==[malloc_3.Reuse two blocks sizes large]==] malloc_3.scalloc [==[malloc_3.scalloc taint]==] [==[malloc_3.scalloc 0 size]==] [==[malloc_3.scalloc Max size num]==] [==[malloc_3.scalloc Max size size]==] [==[malloc_3.scalloc Max size both]==] [==[malloc_3.Split block]==] [==[malloc_3.Split block under threshold]==] [==[malloc_3.Split block threshold]==] [==[malloc_3.Merge with prev block]==] [==[malloc_3.Merge with prev block pad]==] [==[malloc_3.Merge with next block]==] [==[malloc_3.Merge with next block pad]==] [==[malloc_3.Merge with both blocks]==] [==[malloc_3.Merge with both blocks pad]==] malloc_3.realloc [==[malloc_3.realloc shrink]==] [==[malloc_3.srealloc Max size]==] [==[malloc_3.srealloc case a]==] [==[malloc_3.srealloc case a split]==] [==[malloc_3.srealloc case a mmap]==] [==[malloc_3.srealloc case b]==] [==[malloc_3.srealloc case b metadata]==] [==[malloc_3.srealloc case b split]==] [==[malloc_3.srealloc case b wilderness]==] [==[malloc_3.srealloc case b wilderness 2]==] [==[malloc_3.srealloc case c]==] [==[malloc_3.srealloc case c 2]==] [==[malloc_3.srealloc case d]==] [==[malloc_3.srealloc case d metadata]==] [==[malloc_3.srealloc case d split]==] [==[malloc_3.srealloc case e]==] [==[malloc_3.srealloc case e no pad]==] [==[malloc_3.srealloc case e split]==] [==[malloc_3.srealloc case fi]==] [==[malloc_3.srealloc case fii]==] [==[malloc_3.srealloc case g]==] [==[malloc_3.srealloc case h]==])
