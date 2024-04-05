import java.util.InputMismatchException;
import java.util.Scanner;
public class MenuClass {
    private static MenuClass instance = null;
    private Scanner scanner;
    private ServiceClass service;

    private MenuClass() {
        scanner = new Scanner(System.in);
        service = new ServiceClass();
    }

    public static MenuClass getInstance() {
        if (instance == null) {
            instance = new MenuClass();
        }
        return instance;
    }

    public void displayMenu() {
        System.out.println("Welcome to the Menu!");
        System.out.println("1. Add a planet");
        System.out.println("2. Add a satellite");
        System.out.println("3. Add a planet system");
        System.out.println("4. Add a star");
        System.out.println("5. Add a star system");
        System.out.println("6. Add a center planet to a planet system");
        System.out.println("7. Add a satellite to a planet system");
        System.out.println("8. Add a center star to a star system");
        System.out.println("9. Add a planet system to a star system");

        System.out.println("10. Show existing planets");
        System.out.println("11. Show existing satellites");
        System.out.println("12. Show existing planet systems");
        System.out.println("13. Show existing stars");
        System.out.println("14. Show existing star systems");

        System.out.println("15. Create a SpaceShip.");
        System.out.println("16. Show SpaceShip Specifics");

        System.out.print("17. Exit menu.");
        System.out.print("Enter your choice: ");
    }


    public void processChoice() {
        int choice;
        do {
            displayMenu();
            choice = scanner.nextInt();
            switch (choice) {
                case 1 -> addPlanet();
                case 2 -> addSatellite();
                case 3 -> addPlanetSystem();
                case 4 -> addStar();
                case 5 -> addStarSystem();
                case 6 -> addCenterPlanet();
                case 7 -> addSatelliteToSystem();
                case 8 -> addCenterStar();
                case 9 -> addPlanetSystemToStarSystem();
                case 10 -> service.showPlanets();
                case 11 -> service.showSatellites();
                case 12 -> service.showPlanetSystems();
                case 13 -> service.showStars();
                case 14 -> service.showStarSystems();
                case 15 -> CreateSpaceShip();
                case 16 -> service.showSpaceShip();
                //case 17 -> service.setDestination();
                //case 18 -> service.updateSpeed();
                //.....
                case 17 -> System.out.println("Exiting...");
                default -> System.out.println("Invalid choice. Please try again.");
            }
        } while (choice != 8);
    }

    private void addPlanet() {
        String name = null;
        double diameter = 0;
        double gravPull = 0;
        boolean pLife = false;
        double X = 0;
        double Y = 0;
        double Z = 0;


        System.out.println("Enter a name for this planet: ");
        name = scanner.next();

        boolean validDiameterInput = false;
        do {
            try {
                System.out.println("Enter the size of the planet (the diameter in km): ");
                diameter = scanner.nextDouble();
                validDiameterInput = true;
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a valid number.");
                scanner.next();
            }
        } while (!validDiameterInput);

        boolean validGravPullInput = false;
        do {
            try {
                System.out.println("Enter the gravitation force of the planet: ");
                gravPull = scanner.nextDouble();
                validGravPullInput = true;
            } catch (InputMismatchException e) {
                System.out.println("Invalid input type.Please enter a valid number.");
                scanner.next();
            }
        } while (!validGravPullInput);


        System.out.println("Possible life sustainable? (true/false): ");
        pLife = scanner.nextBoolean();


        boolean validCoordinatesInput = false;
        do {
            try {
                System.out.println("Enter the coordinates of the planet:");
                System.out.println("Enter the X coordinate:");
                X = scanner.nextDouble();

                System.out.println("Enter the Y coordinate:");
                Y = scanner.nextDouble();

                System.out.println("Enter the Z coordinate:");
                Z = scanner.nextDouble();

                validCoordinatesInput = true;
            } catch (InputMismatchException e) {
                System.out.println("Invalid input type. Please enter valid numbers.");
                scanner.nextLine();
            }
        } while (!validCoordinatesInput);

        Coordinates coods = new Coordinates(X, Y, Z);
        Planet planet = new Planet(name, diameter, gravPull, pLife, coods);
        service.m_planetsArray.add(planet);
    }


    private void addSatellite() {

        System.out.println("Enter a name for this satellite: ");
        String name = scanner.next();

        System.out.println("Enter the size of the satellite(the diameter in km): ");
        double diameter = scanner.nextDouble();

        System.out.println("Enter the gravitation force of the satellite: ");
        double gravPull = scanner.nextDouble();

        System.out.println("Enter the coordinates of the satellite:");
        System.out.println("Enter the X coordinate:");
        double X = scanner.nextDouble();

        System.out.println("Enter the Y coordinate:");
        double Y = scanner.nextDouble();

        System.out.println("Enter the Z coordinate:");
        double Z = scanner.nextDouble();

        Coordinates coords = new Coordinates(X, Y, Z);
        Satellite satellite = new Satellite(name, diameter, gravPull, coords );

        service.m_satellitesArray.add(satellite);
    }

    private void addPlanetSystem() {

        System.out.println("Enter a name for this planet system: ");
        String name = scanner.next();

        PlanetSystem planetSystem = new PlanetSystem(name);

        if(service.getPlanetSystemByName(name) == null) {
            service.m_planetsystemsArray.add(planetSystem);
        }
        else {
            System.out.println("This planet system already exists.");
        }

    }

    private void addCenterPlanet(){
        System.out.println("Enter a name of the planet system: ");
        String planetSystem = scanner.next();
        PlanetSystem planetSystem1 = service.getPlanetSystemByName(planetSystem);
        if (planetSystem1 == null)
            System.out.println("No such planet system exists.");
        else {
            if (planetSystem1.getCenterPlanet()!= null) {
                System.out.println("This planet system already has a center planet");
            }

            System.out.println("Enter a name for the center planet: ");
            String centerPlanet = scanner.next();
            Planet planet = service.getPlanetByName(centerPlanet);
            if (planet == null) {
                System.out.println("No such planet exists.");
            }
            else {
                planetSystem1.setPlanet(planet);
            }
        }

    }

    private void addSatelliteToSystem(){
        System.out.println("Enter a name of the planet system: ");
        String planetSystem = scanner.next();
        PlanetSystem planetSystem1 = service.getPlanetSystemByName(planetSystem);
        if (planetSystem1 == null)
            System.out.println("No such planet system exists.");
//        else {
//            if ()
//                System.out.println("This satellite is already in this system");
//        }

        System.out.println("Enter a name for the satellite: ");
        String sat = scanner.next();
        Satellite satellite = service.getSatelliteByName(sat);
        if (satellite == null)
            System.out.println("No such satellite exists.");
    }

    private void addStar() {

        System.out.println("Enter a name for this star: ");
        String name = scanner.next();

        System.out.println("Enter the size of the star(the diameter in km): ");
        double diameter = scanner.nextDouble();

        System.out.println("Enter the gravitation force of the star: ");
        double gravPull = scanner.nextDouble();

        System.out.println("Enter the coordinates of the star:");
        System.out.println("Enter the X coordinate:");
        double X = scanner.nextDouble();

        System.out.println("Enter the Y coordinate:");
        double Y = scanner.nextDouble();

        System.out.println("Enter the Z coordinate:");
        double Z = scanner.nextDouble();

        Coordinates coods = new Coordinates(X, Y, Z);
        Star star = new Star(name, diameter, gravPull, coods );

        service.m_starsArray.add(star);
    }


    private void addStarSystem() {

        System.out.println("Enter a name for this star system: ");
        String name = scanner.next();

        StarSystem starSystem = new StarSystem(name);
        if(service.getStarSystemByName(name) == null) {
            service.m_starSystemList.add(starSystem);
        }
        else {
            System.out.println("This star system already exists.");
        }

    }

    private void addCenterStar(){
        System.out.println("Enter a name of the star system: ");
        String starSystem = scanner.next();
        StarSystem starSystem1 = service.getStarSystemByName(starSystem);
        if (starSystem1 == null)
            System.out.println("No such star system exists.");
        else {
            if (starSystem1.getCenteStar() != null) {
                System.out.println("This star system already has a center star");
            }

            System.out.println("Enter a name for the center star: ");
            String centerStar = scanner.next();
            Star star = service.getStarByName(centerStar);
            if (star == null) {
                System.out.println("No such star exists.");
            }
            else {
                starSystem1.setStar(star);
            }
        }

    }

    private void addPlanetSystemToStarSystem(){
        System.out.println("Enter a name of the star system: ");
        String starSystem = scanner.next();
        StarSystem starSystem1 = service.getStarSystemByName(starSystem);
        if (starSystem1 == null)
            System.out.println("No such star system exists.");
        else {
//            if ()
//                System.out.println("This planet system is already in this system");
            System.out.println("Enter a name for the planet system: ");
            String planetSystem = scanner.next();
            PlanetSystem planetSystem1 = service.getPlanetSystemByName(planetSystem);
            if (planetSystem1 == null) {
                System.out.println("No such planet system exists.");
            }
            else{
                starSystem1.addPlanetSystem(planetSystem1);
            }
        }


    }


    private void CreateSpaceShip()
    {
        System.out.println("Enter a name for this SpaceShip: ");
        String name = scanner.next();

        System.out.println("Enter the speed of the Spaceship: ");
        double speed = scanner.nextDouble();

        System.out.println("Enter the direction angle of the SpaceShip: ");
        double dirAngle = scanner.nextDouble();

        service.spaceShip = new SpaceShip(name, speed, dirAngle);;
        //service.m_starsArray.add(star);
    }


}
