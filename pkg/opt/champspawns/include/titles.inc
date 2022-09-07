const CHAMPION_GREED      := 1;
const CHAMPION_POWER      := 2;

function GetSkullTypes()
  var champions := dictionary;
  champions[CHAMPION_GREED]    := "Greed";
  champions[CHAMPION_POWER]    := "Power";
  return champions;
endfunction

function GetSkullType(champion_id)
  var champions := GetSkullTypes();
  return champions[champion_id];
endfunction
