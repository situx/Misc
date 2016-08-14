import java.util.LinkedList;
public class Knoten {
		int zahl=-1;
		Knoten rechts=null;
		Knoten links=null;
		boolean status=false;
		public Knoten(int zahl, Knoten links,Knoten rechts,boolean status) {
			this.zahl = zahl;
			this.rechts = rechts;
			this.links = links;
			this.status=status;
		}
		@Override
		public String toString() {
			return zahl+"";
			}
		public void AddNode(int wert){
			Knoten k=this;
			if (wert<k.zahl){
				if (k.links==null)
					k.links=new Knoten(wert,null,null,true);
				else{
					k=k.links;
					k.AddNode(wert);
					}
				}
			if (wert>k.zahl){
				if (k.rechts==null)
					k.rechts=new Knoten(wert,null,null,true);
				else{
					k=k.rechts;
					k.AddNode(wert);
					}
				}
		}
		public void SearchNode(int wert){
			Knoten k=this;
			if (k.zahl==wert && k.status==true)
				System.out.print("Zahl "+wert+" gefunden!");
			else if (wert>k.zahl && k.rechts!=null){
				k=k.rechts;
				System.out.print("rechts->");
				k.SearchNode(wert);
			}
			else if (wert<k.zahl && k.links!=null){
				k=k.links;
				System.out.print("links->");
				k.SearchNode(wert);
			}
			else if ((k.zahl<wert && k.links==null) || (k.zahl>wert && k.rechts==null))
				System.out.print("Die Zahl ist nicht vorhanden!");
		}
		public static void InOrder(Knoten k){
			if (k.links!=null)
				InOrder(k.links);
			System.out.print(k.zahl+"|");
			if (k.rechts!=null)
				InOrder(k.rechts);
			}			
		public static void PostOrder(Knoten k){
			if (k.links!=null)
				PostOrder(k.links);
			if (k.rechts!=null)
				PostOrder(k.rechts);
			System.out.print(k.zahl+"|");
			}			
		public static void PreOrder(Knoten k){
			System.out.print(k.zahl+"|");
			if (k.links!=null)
				PreOrder(k.links);
			if (k.rechts!=null)
				PreOrder(k.rechts);
			}
		public static void LevelOrder(Knoten k){
			LinkedList<Knoten> q=new LinkedList<Knoten>();
			q.add(k);
			while (q.isEmpty()==false)
			{
				Knoten n=q.getFirst();
				q.removeFirst();
				System.out.print(n.zahl+"|");
				if (n.links!=null)
					q.add(n.links);
				if (n.rechts!=null)
					q.add(n.rechts);	
			}
			}
		public void DeleteNode(int wert){
			int i=0,pos=0,j=0;
			Knoten l=this;
			Knoten k=this;
			Knoten m=this;
			Knoten n=this;
			Knoten o=this;
			Knoten p=this;
			while (k!=null){
			if (k.zahl==wert && k.status==true)
				break;
			else if (wert>k.zahl && k.rechts!=null){
				l=k;
				k=k.rechts;
			}
			else if (wert<k.zahl && k.links!=null){
				l=k;
				k=k.links;
			}
			else if ((k.zahl<wert && k.links==null) || (k.zahl>wert && k.rechts==null))
				break;
		}
		if (k.zahl==wert)
		{
			if (k.links==null && k.rechts==null){
				if (l.zahl>k.zahl)
					l.links=null;
				else
					l.rechts=null;
			}
			else if (k.rechts==null && k.links!=null)
			{
				if (l.zahl>k.zahl)
				l.links=k.links;
				else
				l.rechts=k.links;
			}
			else if (k.rechts!=null && k.links==null)
			{
				if (l.zahl>k.zahl)
					l.links=k.rechts;
					else
					l.rechts=k.rechts;
			}
			else if (k.rechts!=null && k.links!=null)
			{
					p=k.rechts;
					m=k.rechts;
					while (m.links!=null){
						n=m;
						m=m.links;
					}
					if (m.links==null && m.rechts==null){
						//k=n.links;
						//n.links=null;
						m.links=k.links;
						k=m;
						m.rechts=null;
						if (l.zahl>k.zahl)
							l.links=k;
						else
							l.rechts=k;		
					}
					else if (m.links==null && m.rechts!=null){
						k.zahl=m.zahl;
						m.zahl=m.rechts.zahl;
						if (m.rechts.links!=null)
							m.links=m.rechts.links;
						else
							m.links=null;
						if (m.rechts.rechts!=null)
							m.rechts=m.rechts.rechts;
						else
							m.rechts=null;
					}
				}
			}
		else 
			System.out.println("Der Knoten existiert nicht");
		}
		public static void main(String[] args) {
			Knoten root=new Knoten(5,null,null,true);
			root.AddNode(3);
			root.AddNode(8);
			root.AddNode(4);
			root.AddNode(1);
			root.AddNode(34);
			root.AddNode(5);
			root.AddNode(2);
			root.AddNode(6);
			root.AddNode(10);
			root.AddNode(36);
			root.AddNode(15);
			root.AddNode(13);
			System.out.println("Preorder:");
			PreOrder(root);
			System.out.println("\nInorder:");
			InOrder(root);
			System.out.println("\nPostorder:");
			PostOrder(root);
			System.out.println("\nLevelorder:");
			LevelOrder(root);
			System.out.println("\nSuche:");
			root.SearchNode(3);
			root.DeleteNode(15);
			System.out.println("\nLevelorder:");
			LevelOrder(root);
		}
		}
