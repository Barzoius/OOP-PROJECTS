
//Clase:
//Planet 1
//Satellite 2
//Star - Dwarf-Star
//     - Planet-hosting 5
//PlanetSystem(One Planet + Multiple Satellite) 6
//StarSystems(One Star + Multiple PlanetSystems) 7
//Constelatii 8
// SpaceShip 9

//Actiuni:
//Calcularea distantei dintre doua obiecte 1
//Cautarea celei mai apropiate planete locuibile de nava 2
//Calcularea pozitiei relative fata de Stea 3
//Aflarea Satelitilor unei Planete 4
//Cautarea stelei dupa constelatie 5
//Schimbarea directiei navei 7
//Aproximarea duratei de timp pana intr-o locatie 8
//Aflarea daca o planeta poate fi habitabila 9
//Polarizarea coordonatelor 10 ?poate?


//import java.util.*;
public class Main {
    public static void main(String[] args) {
//        Planet earth = new Planet("Earth", 12742, 3.986 * Math.pow(10, 14), true, new Coordinates(0.3, 0, 0));
//        System.out.println(earth.toString());
//
//        Satellite moon = new Satellite("Moon", 3432, 1.23 * Math.pow(10, 14));
//        System.out.println(moon.toString());

        Planet earth = new Planet("Earth", 12742, 3.986 * Math.pow(10, 14), true, new Coordinates(0.3, 0, 0));
        Satellite moon = new Satellite("Moon", 3432, 1.23 * Math.pow(10, 14), new Coordinates(0.3, 0.0, 0));
        Planet mars = new Planet("Mars", 132323, 2.43 * Math.pow(10, 14), false, new Coordinates(0.3, 1.0, 0));
        Satellite phobos = new Satellite("Phobos", 2345, 1.1 * Math.pow(10, 14), new Coordinates(0.3, 0, 0));

        // Create a PlanetSystem
        PlanetSystem earthsys = new PlanetSystem("Earth's system");
        PlanetSystem newsys = new PlanetSystem("");

        earthsys.setPlanet(earth);
        earthsys.addSatellite(moon);
        earthsys.addSatellite(phobos);
        newsys.setPlanet(mars);
        newsys.addSatellite(phobos);

        System.out.println(earthsys);

        System.out.println(newsys);

        Star Sun = new Star("SUN", 122345, 7.1 * Math.pow(10, 14), new Coordinates(0.7, 0, 0));

        StarSystem SolarSys = new StarSystem("SolarSystem");
        SolarSys.setStar(Sun);
        SolarSys.addPlanetSystem(earthsys);
        SolarSys.addPlanetSystem(newsys);

        System.out.println(SolarSys);

        ServiceClass serviciu = new ServiceClass();
        System.out.println(serviciu.computeDistance(earth, Sun));

        serviciu.starSystemList.add(SolarSys);
        serviciu.polarizeCoordinates(new Coordinates(1.23, 32.2, 0.0));

        System.out.println(serviciu.isInArea(SolarSys, earth));
    }
}