use uo;
use os;

include "include/client";

function StoreDamage(attacker, defender, damage)

	var attacker_list := GetObjProperty(defender, "AttackerList");

	if (!attacker_list)
		attacker_list := dictionary;
	endif

	var attacker_serial := CInt(attacker.serial);
	
	if (!attacker_list.Exists(attacker_serial))
		attacker_list[attacker_serial] := damage;
	else
		attacker_list[attacker_serial] += damage;
	endif
	SetObjProperty(defender, "AttackerList", attacker_list);

	if (!GetObjProperty(defender, "MyMaxHP"))
		SetObjProperty(defender, "MyMaxHP", GetMaxHP(defender));
	endif

endfunction

		