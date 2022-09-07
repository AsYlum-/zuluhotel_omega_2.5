use uo;
use os;
use util;
use basic;
use cfgfile;
use attributes;

include "include/attributes";
include "include/classes";

function get_default_points(skillid)
        var cfg := readconfigfile(":shilhook:attributes");

        var default_points := FindConfigElem( cfg, GetAttributeIdBySkillId( skillid ) ).DefaultPoints;
        
        if (!default_points)
                return 0;
        else
                return default_points;

        endif

endfunction


function AwardSkillPoints( who, skillid, points )

  // NPCS don't gain skill
	if( who.IsA(POLCLASS_NPC) )
		return 0;
	// staff don't gain skill
	elseif( who.cmdlevel )
		return 0;
	endif

  	// Get lock/drop/raise status of the skills
	var skills_state_array   := GetObjProperty( who, "SkillsState" );
	if( !skills_state_array )
		skills_state_array := array;
	endif
	
	// Get the lock/drop/raise status of THIS skill
	var skill_state := skills_state_array[skillid+1];
	
	// Skill is set to drop
	if( skill_state == "d" )
		var baseskill := GetBaseSkill( who, skillid );
		var amount   := 1;
		//amount to drop is more than the skill he has, set skill to 0 and LOCK the skill
		if( amount > baseskill )
			amount := baseskill;
			skills_state_array[skillid+1] := "l";
			SetObjProperty( who, "SkillsState", skills_state_array );
		endif
		// Reduce skill points
		SetBaseSkill( who, skillid, Cint(baseskill - amount) );
		return 0;
		
		// Skill is set to locked, just return 0
	elseif( skill_state == "l" )
		return 0;
	endif
	
	//-------- Skill is set to RAISE, do some gain ---------\\
	
	// Check if the player has any skill modifier set, set by admins using .setplayermultipliers. Should never happen...
	points := Cint( points * GetSkillPointsMultiplier( who , skillid ) );
	var special_multipliers := GetObjProperty( who, "SkillMultipliers" );
	if( len(special_multipliers) )
		if( special_multipliers[skillid+1] )
			if( Cint(special_multipliers[skillid+1]) == 9999 )
				points := 0;
			else
				var skill_mult := Cdbl( special_multipliers[skillid+1] );
				points := Cint( points * skill_mult );
			endif
		endif
	endif
	
	// Check if any global mulitpliers are set for this skill, using .setglobalmultipliers. power hour anyone? :P
	var global_multipliers := GetGlobalProperty( "SkillPointsMultiplier" );
	if( len(global_multipliers) )
		if( global_multipliers[skillid+1] )
			if( Cint(global_multipliers[skillid+1]) == 9999 )
				points := 0;
			else
				var mult := Cdbl( global_multipliers[skillid+1] );
				points := Cint( points * mult );
			endif
		endif
	endif
	
	//Bonus for everyone
	points := Cint( points * 1.4 );

	//Bonus for first gen players
	if(who.acct.GetProp("FirstGen"))
		points := Cint( points * 1.1 );
	endif	

	//Powerhour
	if(GetGlobalProperty("PHS") || GetObjProperty(who, "#PPHS"))
		points := Cint( points * 2 );
	endif	

	//RPers receive increased skill gain due to no macroing rules.
	if(GetObjProperty(who, "IsRPer"))
		points := Cint( points * 1.5 );
	endif	

	//Powerplayer increased skill gain (classbonus)
	if (GetObjProperty(who, CLASSEID_POWERPLAYER))
	var level := GetClasseLevel(who);
		case(level)
			3: points := Cint( points * 1.1 );
			4: points := Cint( points * 1.2 );
			5: points := Cint( points * 1.3 );
		endcase
	endif

	// Set the skill points
	AwardPoints(who, skillid, points);
	
endfunction
