import Control.Monad.State
import Data.List
import Data.Functor.Identity

removeMax :: (Num a, Eq a, Ord a) => State [a] a
removeMax = StateT $
            \list -> let maxNum = maximum list
                     in Identity (maxNum, delete maxNum list)

removeMaxThreeTimes ::
  (Num a, Eq a, Ord a) => State [a] (a, a, a)
removeMaxThreeTimes = do
  x <- removeMax
  y <- removeMax
  z <- removeMax
  return (x, y, z)

removeMaxThreeTimesBind ::
  (Num a, Eq a, Ord a) => State [a] (a, a, a)
removeMaxThreeTimesBind = removeMax >>=
                          (\x -> removeMax >>=
                            (\y -> removeMax >>=
                              (\z -> return ((x, y, z)))))

playString :: String -> State (Integer, Integer) Integer
playString []     = do
  (player1, player2) <- get
  if player1 < player2 then return 2
    else
    if player2 < player1
    then return 1
    else return 0
playString (x:xs) = do
  (player1, player2) <- get
  case x of
    'a' -> put (player1 + 1, player2)
    'b' -> put (player1 + 2, player2)
    'c' -> put (player1, player2 + 1)
    'd' -> put (player1, player2 + 2)
    _   -> put (player1, player2)
  playString xs
