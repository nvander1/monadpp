import Test.HUnit
test1 = TestCase (assertEqual "Just monad test 1,"
                  (do
                      x <- Just 3
                      y <- Just 10
                      z <- Nothing
                      return (x + y + z)
                  )
                  (Nothing)
                 )

test2 = TestCase (assertEqual "Just monad test 2,"
                  (
                    Just 3 >>= (\x -> Just 10 >>= (\y -> Nothing >>= (\z -> return (x + y + z))))
                  )
                  (Nothing)
                 )

test3 = TestCase (assertEqual "List monad test 1,"
                  (do
                      x <- [1, 2, 5, 10]
                      return $ print x
                      if odd x then [x, -x] else [x]
                  )
                  [1, -1, 2, 5, -5, 10]
                 )

test4 = TestCase (assertEqual "List monad test 2,"
                  (
                    [1, 2, 5, 10] >> [1, 2]

                  )
                  [1, 2, 1, 2, 1, 2, 1, 2]
                 )


tests = TestList [TestLabel "test1" test1, TestLabel "test2" test2,
                  TestLabel "test3" test3, TestLabel "test3" test3]

oddEvenList :: (Integral a) => [a] -> [a]
oddEvenList list = do
  x <- list
  if odd x then [x, -x] else [x]

oddEvenListBind :: (Integral a) => [a] -> [a]
oddEvenListBind list = list >>= (\x -> if odd x then [x, -x] else [x])

doubleMonad :: [a] -> [a]
doubleMonad list = [-1, 2] >> list

nothingMonadDo = do
  x <- Just 3
  y <- Just 10
  z <- Nothing
  return (x + y + z)

nothingMonadBind = Just 3 >>= (\x -> Just 10 >>= (\y -> Nothing >>= (\z -> return (x + y + z))))

justMonadDo = do
  x <- Just 3
  y <- Just 10
  z <- Just 11
  return (x + y + z)

justMonadBind = Just 3 >>= (\x -> Just 10 >>= (\y -> Just 11 >>= (\z -> return (x + y + z))))


-- example2 =

main :: IO Counts
main = runTestTT $ tests
