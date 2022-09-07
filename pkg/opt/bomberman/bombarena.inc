use uo;

function createArena()
	var i;
	for(i := 0;i<20; i:=i+1)
		CreateItemAtLocation( 5508+i, 1674, 0, 0x9A94 );
		CreateItemAtLocation( 5508, 1674-i, 0, 0x9A94 );

		if(i%2 == 0)
			CreateItemAtLocation( 5509, 1674-i, 0, 0x9A94 );
			CreateItemAtLocation( 5511, 1674-i, 0, 0x9A94 );
			CreateItemAtLocation( 5513, 1674-i, 0, 0x9A94 );
			CreateItemAtLocation( 5515, 1674-i, 0, 0x9A94 );
			CreateItemAtLocation( 5517, 1674-i, 0, 0x9A94 );
			CreateItemAtLocation( 5519, 1674-i, 0, 0x9A94 );
			CreateItemAtLocation( 5521, 1674-i, 0, 0x9A94 );
			CreateItemAtLocation( 5523, 1674-i, 0, 0x9A94 );
			CreateItemAtLocation( 5525, 1674-i, 0, 0x9A94 );
		endif
	endfor
	return;
endfunction