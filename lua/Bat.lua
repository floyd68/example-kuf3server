local randomMoveTime = 0.0

function Update(time_value)
	if(ai_class:ready(time_value) == false) then
		return
	end
	
	randomMoveTime = randomMoveTime + time_value
	
	if(randomMoveTime > 1.0) then
		ai_class:ChangeRandomDir()
		randomMoveTime = 0.0
	end
end

function OutScreen()
	if(randomMoveTime > 1.0) then
		ai_class:update_random_pos()
		randomMoveTime = 0.0
	end
end