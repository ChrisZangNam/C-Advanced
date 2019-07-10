#include<string.h>
GtkTreeModel        *model;
enum
{
  COL_NAME = 0,
  NUM_COLS
} ;


static GtkTreeModel *
create_and_fill_model (char a[][100],int k)
{
  GtkListStore  *store;
  GtkTreeIter    iter;

  store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_UINT);

  /* Append a row and fill in some data */
  int i=0;


  for(;i<k;i++)
  {
      //char a[2][2]={"a","b"};
      gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter,
                      COL_NAME, a[i],
                      -1);
  }

  return GTK_TREE_MODEL (store);
}

static GtkWidget *
create_view_and_model (char a[][100],int k)
{
  GtkCellRenderer     *renderer;

  GtkWidget           *view;

  view = gtk_tree_view_new ();

  /* --- Column #1 --- */

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                               -1,
                                               "Word list",
                                               renderer,
                                               "text", COL_NAME,
                                               NULL);

  /* --- Column #2 --- */



  model = create_and_fill_model (a,k);

  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  /* The tree view has acquired its own reference to the
   *  model, so we can drop ours. That way the model will
   *  be freed automatically when the tree view is destroyed */

  g_object_unref (model);

  return view;
}
