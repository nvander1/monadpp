import Test.HUnit
test1 = TestCase (assertEqual "test 1,"
                  (do 
                     x <- Just 3
                     y <- Just 10
                     z <- Nothing
                     return (x + y + z)
                  )
                  (Nothing)
                 )
tests = TestList [TestLabel "test1" test1, TestLabel "test2" test2]

test2 = TestCase (assertEqual "test 2,"
                  (
                    Just 3 >>= (\x -> Just 10 >>= (\y -> Nothing >>= (\z -> return (x + y + z))))
                  )
                  (Nothing)
                 )
