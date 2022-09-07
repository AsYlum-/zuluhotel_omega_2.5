// Made by a Giraffe

include ":housing:setup";

function StaticHouseSerial( who )

	foreach item_type in tile_list
		foreach item in ListItemsNearLocationOfType( who.x,who.y, who.z, 0, item_type );
			if( GetObjProperty( item, "HousePlate" ) AND ( GetObjProperty( item, "houseserial" ) ) )
				return GetObjProperty( item, "houseserial" );
			endif
		endforeach
	endforeach	
	
	return 0;
endfunction

function StaticHouseSerialAtLocation( x, y, z )

	foreach item_type in tile_list
		foreach item in ListItemsNearLocationOfType( x, y, z, 0, item_type );
			if( GetObjProperty( item, "HousePlate" ) AND ( GetObjProperty( item, "houseserial" ) ) )
				return GetObjProperty( item, "houseserial" );
			endif
		endforeach
	endforeach

	return 0;
endfunction
