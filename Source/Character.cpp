//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Character.hpp"

Character::Character(std::string name)
{
	entityType = "Character";
	entityAnimator.setPath("Sprites/Character/" + name);
	entityAnimator.loadAnimator();
	entityAnimator.setKey("IDLE_RIGHT");
	DataParser characterMoves;
	characterMoves.parseFile("Data/Stats/Player/Moves.sta.msd");
	characterMoves.getAttribute("BasicMoves", "", "walkSpeed")->getData(&maxWalkSpeed);
	characterMoves.getAttribute("BasicMoves", "", "runSpeed")->getData(&maxRunSpeed);
	characterMoves.getAttribute("BasicMoves", "", "jumpHeight")->getData(&maxJumpHeight);
}

void Character::setDirectionAnimation(std::string animation)
{
	if (direction == "Left")
		entityAnimator.setKey(animation+"_LEFT");
	else
		entityAnimator.setKey(animation+"_RIGHT");
}

void Character::melee(int x, int y)
{
}

void Character::verticalUpdate()
{
	if (!isJumping && !isFalling)
	{
		if (!collide( 0, 1))
		{
			isFalling = true;
			fallIterate = 0;
			fallCounter = 0;
			speedFall = 0;
		}
		else
		{
			isFalling = false;
			fallByJump = false;
			fallIterate = 0;
			fallCounter = 0;
			speedFall = 0;
		}
	}
	else if (isJumping)
	{
		if (jumpInc > 0)
		{
			if (!collide( 0, -jumpInc*currentDeltaTime - 1))
			{
				addDtPos(0, -jumpInc);
				jumpInc -= currentDeltaTime;
				jumpIterate++;
			}
			else
			{
				isJumping = false;
				isFalling = true;
				jumpInc = 0;
				jumpIterate = 0;
			}
		}
		else
		{
			isJumping = false;
			isFalling = true;
			jumpIterate = 0;
		}
	}
	else if (isFalling)
	{
		fallIterate += currentDeltaTime;
		fallCounter++;
		setDirectionAnimation("FALL");
		if (!collide( 0, speedFall*currentDeltaTime))
		{
			addDtPos(0, speedFall);
			if (speedFall < 70)
				speedFall += currentDeltaTime;
		}
		else
		{
			if (fallIterate >= 50)
			{
				life -= ((int)fallIterate - 50);
				isCrouching = true;
			}
			else if (fallIterate >= 30 && speed < maxWalkSpeed)
			{
				isCrouching = true;
			}
			else if (fallIterate >= 30 && speed >= maxWalkSpeed)
			{
				setDirectionAnimation("RECOVER");
				speed += (fallIterate - 30) * (speed*2/maxRunSpeed);
			}
			isFalling = false;
			fallIterate = 0;
			fallCounter = 0;
			speedFall = 0;
			if (!collide( 0, 0))
			{
				while (!collide( 0, 0))
				{
					addPos(0, 1);
				}
				isFalling = false;
				fallIterate = 0;
				fallCounter = 0;
				speedFall = 0;
			}
		}
	}
}

void Character::jump()
{
	if (!isCrouching)
	{
		if (!isJumping && !isFalling)
		{
			if (maxRunSpeed != speed)
				setDirectionAnimation("JUMP");
			else if (maxRunSpeed == speed)
				setDirectionAnimation("SIDEFLIP");
			isJumping = true;
			jumpIterate = 0;
			jumpInc = maxJumpHeight;
			fallByJump = true;
		}
		else if (!isJumping && isFalling && !fallByJump && fallIterate < 5)
		{
			if (maxRunSpeed != speed)
				setDirectionAnimation("JUMP");
			else if (maxRunSpeed == speed)
				setDirectionAnimation("SIDEFLIP_LEFT");
			isJumping = true;
			jumpIterate = 0;
			jumpInc = maxJumpHeight;
			fallByJump = true;
			isFalling = false;
			speedFall = 0;
		}
		else if ((isJumping || isFalling) && (jumpIterate >= 15 || fallIterate < 40))
		{
			if (collide( -1, 0) && direction == "Left")
			{
				direction = "Right";
				entityAnimator.setKey("SIDEFLIP_RIGHT");
				velocity = 15;
				isJumping = true;
				isFalling = false;
				jumpInc = maxJumpHeight;
				fallByJump = true;
				speedFall = 0;
				fallIterate = 0;
				fallCounter = 0;
				jumpIterate = 0;
			}
			else if (collide( 1, 0) && direction == "Right")
			{
				direction = "Left";
				entityAnimator.setKey("SIDEFLIP_LEFT");
				velocity = -15;
				isJumping = true;
				isFalling = false;
				jumpInc = maxJumpHeight;
				fallByJump = true;
				speedFall = 0;
				fallIterate = 0;
				jumpIterate = 0;
			}
		}
	}
	else
	{
		isCrouching = false;
		setDirectionAnimation("RECOVER");
	}
}

void Character::move(std::string cdirection)
{
	this->direction = cdirection;
	isMoving = true;
	if (isCrouching)
	{
		setDirectionAnimation("RECOVER");
		isCrouching = false;
	}
	if (!isJumping && !isFalling)
	{
		speedIterate += currentDeltaTime; //No acceleration in air
	}
	if (abs(velocity) > speed && velocity != 0) //Inerty Cancel
	{
		if (direction == "Left" && velocity > 0)
		{
			velocity -= speed;
			speed = 0;
		}
		else if (direction == "Right" && velocity < 0)
		{
			velocity += speed;
			speed = 0;
		}
	}
	else if (abs(velocity) < speed && velocity != 0)
	{
		velocity = 0;
		speed -= velocity;
	}


	if (isJumping || isFalling)
	{
		downLineClimb = 0;
		upLineClimb = 0;
	}
	else
	{
		if (speed >= 1)
		{
			downLineClimb = -speed;
			upLineClimb = speed;
		}
		else
		{
			downLineClimb = -1;
			upLineClimb = 1;
		}
	}

	if (direction != lastDirection)
	{
		speed = 0;
		speedIterate = 0;
	}
	else
	{
		if (speedIterate >= maxSpeedIterate || speed < maxSpeed / 2)
		{
			if (speed < maxSpeed)
			{
				speed += currentDeltaTime;
			}
			else if (speed > maxSpeed)
			{
				speed -= (currentDeltaTime / 5);
			}
			speedIterate = 0;
		}
	}
		
	if (direction == "Left" && !isCrouching)
	{
		int voffset;
		bool collided = true;
		for (voffset = downLineClimb; voffset <= upLineClimb; voffset++)
		{
			if (!collide(-speed*currentDeltaTime - 1, -voffset - 1))
			{
				addDtPos(-speed, 0);
				addPos(0, -voffset);
				collided = false;
				break;
			}
		}
		if (collided)
		{
			if (collide(-speed*currentDeltaTime - 1, 0) && !collide( 0, 0))
			{	
				for (int tpSp = std::floor(speed); tpSp > 0; tpSp--)
				{
					if (!collide( -tpSp, 0))
					{
						addPos(-tpSp, 0);
						speed = 0;
						break;
					}
				}
			}
		}
	}
	if (direction == "Right" && !isCrouching)
	{
		int voffset;
		bool collided = true;
		for (voffset = downLineClimb; voffset <= upLineClimb; voffset++)
		{
			if (!collide(speed*currentDeltaTime + 1, -voffset - 1))
			{
				addDtPos(speed, 0);
				addPos(0, -voffset);
				bool collided = false;
				break;
			}
		}
		if (collided)
		{
			if (collide(speed*currentDeltaTime + 1, 0) && !collide( 0, 0))
			{
				for (int tpSp = std::floor(speed); tpSp > 0; tpSp--)
				{
					if (!collide( tpSp, 0))
					{
						addPos(tpSp, 0);
						speed = 0;
						break;
					}
				}
			}
		}
	}

	lastDirection = direction;

	if (!isJumping && !isFalling && !isCrouching)
	{
		if (!isSprinting)
			setDirectionAnimation("WALK");
		else
			setDirectionAnimation("RUN");
	}
}

void Character::applyMove(int hWidth)
{
	bool collided = true;
	if (hWidth >= 0)
	{
		if (!collide(hWidth*currentDeltaTime, 0))
		{
			addDtPos(hWidth, 0);
			collided = false;
		}
	}
	else
	{
		if (!collide(hWidth*currentDeltaTime, 0))
		{
			addDtPos(hWidth, 0);
			collided = false;
		}
	}
	
	if (collided)
	{
		speed = 0;
		setDirectionAnimation("IDLE");
	}
}

void Character::textureUpdate()
{
	if (!isMoving && !isJumping && !isFalling)
	{
		if (!isCrouching)
		{
			setDirectionAnimation("IDLE");
		}
		else
		{
			if (speed == 0)
			{
				if (direction == "Left" && entityAnimator.getKey() != "SITTED_LEFT")
				{
					entityAnimator.setKey("SIT_LEFT");
				}
				else if (direction == "Right" && entityAnimator.getKey() != "SITTED_RIGHT")
				{
					entityAnimator.setKey("SIT_RIGHT");
				}
			}
		}
	}
}

void Character::moveUpdate()
{
	if (velocity != 0)
	{
		this->applyMove(velocity);
		if (velocity < 0)
		{
			velocity += currentDeltaTime;
			if (velocity > 0) velocity = 0;
		}
		if (velocity > 0)
		{
			velocity -= currentDeltaTime;
			if (velocity < 0) velocity = 0;
		}
	}
	if (!isMoving)
	{
		if (speed >= 1)
		{
			speed = 0;
		}
	}
	isMoving = false;
	this->verticalUpdate();
}

void Character::sprint(bool activSprint)
{
	if (!isFalling && !isJumping && activSprint)
	{
		isSprinting = activSprint;
	}
	else if (!activSprint)
	{
		isSprinting = false;
	}
	if (isSprinting)
	{
		maxSpeed = maxRunSpeed;
	}
	else
	{
		maxSpeed = maxWalkSpeed;
	}
}

int Character::getHSpeed()
{
	return speed;
}

int Character::getVSpeed()
{
	return speedFall;
}

void Character::triggerCrouch(bool isCrouching)
{
	if (this->isCrouching && !isCrouching)
		setDirectionAnimation("STAND");
	this->isCrouching = isCrouching;
}

std::string Character::getDirection()
{
	return direction;
}

void Character::specialUpdate()
{

}

void Character::cancelMoves()
{
	streamLink->streamPush(std::string("Character Moves Cancelled"));
	speedFall = 0;
	fallIterate = 0;
	fallCounter = 0;
	jumpInc = 0;
	jumpIterate = 0;
	isJumping = false;
	isMoving = false;
	velocity = 0;
	speed = 0;
	fallByJump = false;
	isFalling = false;
	isCrouching = false;
}

void Character::setVelocity(double newinerty)
{
	velocity = newinerty;
}

void Character::addVelocity(double addinerty)
{
	velocity += addinerty;
}

double Character::getVelocity()
{
	return velocity;
}