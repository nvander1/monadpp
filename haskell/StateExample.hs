import Control.Monad.State
import Data.List
import Data.Functor.Identity

removeMax :: (Num a, Eq a, Ord a) => State [a] a
removeMax = StateT $ \list -> let maxNum = maximum list in Identity (maxNum, delete maxNum list)

removeMaxThreeTimes :: (Num a, Eq a, Ord a) => State [a] (a, a, a)
removeMaxThreeTimes = do
  x <- removeMax
  y <- removeMax
  z <- removeMax
  return (x, y, z)

removeMaxThreeTimesBind :: (Num a, Eq a, Ord a) => State [a] (a, a, a)
removeMaxThreeTimesBind = removeMax >>=
                          (\x -> removeMax >>=
                                 (\y -> removeMax >>=
                                        (\z -> return ((x, y, z)))))
