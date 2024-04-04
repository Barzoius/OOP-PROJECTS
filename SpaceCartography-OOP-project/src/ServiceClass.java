import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
public class ServiceClass {

    public List<StarSystem> starSystemList;

    public ServiceClass()
    {
        starSystemList = new ArrayList<>();
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

    private  Coordinates getCoordinates(Object obj) {
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
        }else {
            throw new IllegalArgumentException("ERROR::OBJECT_DOES_NOT_HAVE_COORDINATES");
        }
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

        for(StarSystem starsys : starSystemList)
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



    //------------(SpaceShip_Methods)------------//

    public void setDestination(SpaceShip spaceShip, Coordinates coords) {
        double deltaX = coords.getX() - spaceShip.getCoordinates().getX();
        double deltaY = coords.getY() - spaceShip.getCoordinates().getY();
        double dirAngle = Math.atan2(deltaY, deltaX);
        spaceShip.setDirectionAngle(dirAngle);
    }

    public double aproxTimeToDestination(SpaceShip spaceShip, Coordinates coords){
        double distace = spaceShip.getCoordinates().distanceTo(coords);
        return (distace/(spaceShip.getSpeed()));
    }

    //ceva fucntie pentru update pe locatie
    //   -se resorteaza listele
}
