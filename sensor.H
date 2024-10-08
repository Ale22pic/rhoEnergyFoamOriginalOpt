// Evaluate Ducors sensor
   volScalarField divU  = fvc::div(U) ;
   volScalarField divU2 = divU*divU ;
   volScalarField rotU2 = magSqr(fvc::curl(U)) ;
// Internal field
   forAll(U,icell)
   {
//ducSensor[icell] = max(-divU[icell]/Foam::sqrt(divU2[icell] + rotU2[icell] + eps[icell]),0.) ; // detect compressions
  ducSensor[icell] = Foam::sqrt(divU2[icell]/(divU2[icell] + rotU2[icell] + epsilon)) ; // detect compressions & expansions
   }
//
// Boundary field
   forAll( mesh.boundaryMesh(), iPatch )
   {
    const polyPatch& patch = mesh.boundaryMesh()[iPatch] ;
    if ((patch.type()=="processor") )
     {
      forAll( patch , iface )
      {
      /*Edited*/
    ducSensor.boundaryFieldRef()[iPatch][iface] = max(-divU.boundaryField()[iPatch][iface]/Foam::sqrt(divU2.boundaryField()[iPatch][iface] + rotU2.boundaryField()[iPatch][iface] + eps.boundaryField()[iPatch][iface]),0.) ; //detect compressions
//  ducSensor.boundaryFieldRef()[iPatch][iface] = Foam::sqrt(divU2.boundaryField()[iPatch][iface]/(divU2.boundaryField()[iPatch][iface] + rotU2.boundaryField()[iPatch][iface] + epsilon)) ; //detect compressions & expansions
 
      }
     }
   }
//
