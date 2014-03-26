		      		crt *Position *npos
#Start  			sub npos Map.Homebase.Position Rover.Position
          			ret *a
		      		GTA ang npos
		      		sub ang ang Rover.Heading
#tryagain1 			ifL 0.0 ang #tryagain2
          			add ang ang 360.0    
          			jmp #tryagain1
#tryagain2			ifl ang 360.0 #calc
					sub ang ang 360.0
					jmp #tryagain2
#calc		  		ifL 355.0 ang #CalcStraight
          			ifL 180.0 ang #CalcDoubleRight
		      		ifl 5.0 ang #CalcDoubleLeft
		      		jmp #CalcStraight
#CalcDoubleLeft 	ife Rover.TurningState 1 #NextStep
					ife Rover.TurningState 2 #TurnLeft
					ife Rover.TurningState 3 #TurnDoubleLeft
					ret *l
					ret *l
					ife Rover.TurningState 4 #TurnLeft
					jmp #TurnDoubleLeft
#CalcDoubleRight	ife Rover.TurningState 5 #NextStep
					ife Rover.TurningState 4 #TurnRight
					ife Rover.TurningState 3 #TurnDoubleRight
					ret *r
					ret *r
					ife Rover.TurningState 2 #TurnRight
					jmp #TurnDoubleRight
#CalcStraight		ife Rover.TurningState 1 #TurnDoubleRight
					ife Rover.TurningState 2 #TurnRight
					ife Rover.TurningState 3 #NextStep
					ife Rover.TurningState 4 #TurnLeft
					jmp #TurnDoubleLeft
#TurnDoubleLeft 	ret *l
#TurnLeft			ret *l
					jmp #NextStep
#TurnDoubleRight 	ret *r
#TurnRight			ret *r
					jmp #NextStep
#NextStep			wat
					jmp #Start