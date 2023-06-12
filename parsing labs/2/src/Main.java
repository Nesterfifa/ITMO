import java.io.ByteArrayInputStream;
import java.io.File;
import java.util.Scanner;

public class Main {
    public static void createDotGraph(String dotFormat,String fileName)
    {
        GraphViz gv=new GraphViz();
        gv.addln(gv.start_graph());
        gv.add(dotFormat);
        gv.addln(gv.end_graph());
        // String type = "gif";
        String type = "pdf";
        // gv.increaseDpi();
        gv.decreaseDpi();
        gv.decreaseDpi();
        File out = new File(fileName+"."+ type);
        gv.writeGraphToFile( gv.getGraph( gv.getDotSource(), type ), out );
    }

    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        String dotFormat = new KotlinParser()
                .parse(
                        new ByteArrayInputStream(
                                scanner.nextLine().getBytes())).toString();
        createDotGraph(dotFormat, "DotGraph");
    }
}
