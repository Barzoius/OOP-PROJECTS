import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
public class ServiceClass {

    public List<StarSystem> m_starSystemList;
    public List<Star> m_starsArray;
    public List<Planet> m_planetsArray;
    public List<Satellite> m_satellitesArray;
    public List<PlanetSystem> m_planetsystemsArray;

    protected SpaceShip spaceShip;
    public ServiceClass()
    {
        m_starSystemList = new ArrayList<>();
        m_starsArray = new ArrayList<>();
        m_planetsArray = new ArrayList<>();
        m_planetsystemsArray = new ArrayList<>();
        m_satellitesArray = new ArrayList<>();
    }

    public void polarizeCoordinates(Coordinates coordinate) {
        double x = coordinate.getX();
        double y = coordinate.getY();
        double r = Math.sqrt(x * x + y * y);
        double theta = Math.atan2(y, x); // Angle in radians

        System.out.printf("Polar Coordinates for %s:\n", coordinate);
        System.out.printf("  r = %.3f\n", r);
        System.out.printf("  theta = %.3f\n", theta);
    }
    public double computeDistance(Object obj1, Object obj2)
    {
        Coordinates coord1 = getCoordinates(obj1);
        Coordinates coord2 = getCoordinates(obj2);
        return coord1.distanceTo(coord2);
    }

    private Coordinates getCoordinates(Object obj) {
        if (obj instanceof Planet) {
            return ((Planet) obj).getCoordinates();
        } else if (obj instanceof Star) {
            return ((Star) obj).getCoordinates();
        } else if (obj instanceof Satellite) {
            return ((Satellite) obj).getCoordinates();
        } else if (obj instanceof StarSystem) {
            return ((StarSystem) obj).getCoordinates();
        }else if (obj instanceof PlanetSystem) {
            return ((PlanetSystem) obj).getCoordinates();
        }else if (obj instanceof SpaceShip) {
            return ((SpaceShip) obj).getCoordinates();
        }else {
            throw new IllegalArgumentException("ERROR::OBJECT_DOES_NOT_HAVE_COORDINATES");
        }
    }

    public Star getStarByName(String name) {
        for (Star star : m_starsArray) {
            if (star.getName().equals(name)) {
                return star;
            }
        }
        return null;
    }

    public Planet getPlanetByName(String name) {
        for (Planet planet : m_planetsArray) {
            if (planet.getName().equals(name)) {
                return planet;
            }
        }
        return null;
    }

    public Satellite getSatelliteByName(String name) {
        for (Satellite satellite : m_satellitesArray) {
            if (satellite.getName().equals(name)) {
                return satellite;
            }
        }
        return null;
    }

    public PlanetSystem getPlanetSystemByName(String name) {
        for (PlanetSystem planetSystem : m_planetsystemsArray) {
            if (planetSystem.getName().equals(name)) {
                return planetSystem;
            }
        }
        return null;
    }

    public StarSystem getStarSystemByName(String name) {
        for (StarSystem starSystem : m_starSystemList) {
            if (starSystem.getName().equals(name)) {
                return starSystem;
            }
        }
        return null;
    }
    public boolean isInArea(StarSystem starsys, Object obj)
    {
        double areaRadius = Math.sqrt(starsys.getArea()/ Math.PI);
        Coordinates object_coords = getCoordinates(obj);
        double distance = object_coords.distanceTo(starsys.getCoordinates());
        return distance <= areaRadius;
    }


    public List<Planet> sustainablePlanets()
    {
        List<Planet> planetsWithPossibleLife = new ArrayList<>();

        for(StarSystem starsys : m_starSystemList)
        {
            for (PlanetSystem planetSystem : starsys.getPlanetSystems()) {

                if (planetSystem.getCenterPlanet().getPossibleLife()) {

                    planetsWithPossibleLife.add(planetSystem.getCenterPlanet());
                }
            }
        }

        return planetsWithPossibleLife;
    }


    public static void sortByProximity(List<Planet> planets, Coordinates targetCoords) {
        planets.sort(new Comparator<Planet>() {
            @Override
            public int compare(Planet planet1, Planet planet2) {

                double distanceToPlanet1 = planet1.getCoordinates().distanceTo(targetCoords);
                double distanceToPlanet2 = planet2.getCoordinates().distanceTo(targetCoords);


                return Double.compare(distanceToPlanet1, distanceToPlanet2);
            }
        });
    }


    //------------(ShowObjects_Methods)------------//

    public void showPlanets()
    {
        for(Planet obj : m_planetsArray)
        {
            System.out.println(obj.getName());
        }
    }

    public void showSatellites()
    {
        for(Satellite obj : m_satellitesArray)
        {
            System.out.println(obj.getName());
        }
    }

    public void showPlanetSystems()
    {
        for(PlanetSystem obj : m_planetsystemsArray)
        {
            System.out.println(obj.getName());
        }
    }

    public void showStars()
    {
        for(Star obj : m_starsArray)
        {
            System.out.println(obj.getName());
        }
    }

    public void showStarSystems()
    {
        for(StarSystem obj : m_starSystemList)
        {
            System.out.println(obj.getName());
        }
    }
    public void showSpaceShip()
    {
        if(this.spaceShip != null)
        {
            System.out.println(this.spaceShip);

        }
        else{
            System.out.println("A_SPACESHIP_WAS_NOT_YET_CREATED");
        }

    }

    //------------(SpaceShip_Methods)------------//

    public void setDestination(SpaceShip spaceShip, Coordinates coords) {
        double deltaX = coords.getX() - spaceShip.getCoordinates().getX();
        double deltaY = coords.getY() - spaceShip.getCoordinates().getY();
        double dirAngle = Math.atan2(deltaY, deltaX);
        spaceShip.setDirectionAngle(dirAngle);
        spaceShip.setDestinationCoordinates(coords);
        double initialDistance = spaceShip.getCoordinates().distanceTo(coords);
        //spaceShip.setDistance(initialDistance);
    }

    public double aproxTimeToDestination(SpaceShip spaceShip, Coordinates coords){
        double distace = spaceShip.getCoordinates().distanceTo(coords);
        return (distace/(spaceShip.getSpeed()));
    }

    //ceva functie pentru update pe locatie
    //   -se resorteaza listele
}
