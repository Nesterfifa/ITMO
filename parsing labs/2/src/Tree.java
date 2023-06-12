import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Tree {
    static int cnt = 0;
    String node;
    List<Tree> children;

    public Tree(String node, Tree... children) {
        this(node);
        this.children.addAll(Arrays.stream(children).collect(Collectors.toList()));
    }

    public Tree(String node) {
        this.node = node + cnt++;
        children = new ArrayList<>();
    }

    @Override
    public String toString() {
        StringBuilder ans = new StringBuilder();
        for (Tree t : children) {
            ans.append(node).append("->").append(t.node).append(";").append(t.toString());
        }
        return ans.toString();
    }
}
