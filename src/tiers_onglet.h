#ifndef _TIERS_ONGLET_H
#define _TIERS_ONGLET_H (1)

#include <gtk/gtk.h>

/* START_INCLUDE_H */
/* END_INCLUDE_H */


/* START_DECLARATION */
gint classement_alphabetique_tree ( GtkWidget *tree,
                        GtkCListRow *ligne_1,
                        GtkCListRow *ligne_2 );
GtkTreeStore *gsb_payee_get_tree_store ( void );
GtkWidget *gsb_payee_get_tree_view ( void );
gboolean gsb_payee_update_combofix ( void );
void gsb_gui_update_payee_toolbar ( void );
GtkWidget *onglet_tiers ( void );
void payee_fill_tree ( void );
gboolean payee_hold_position_set_expand ( gboolean expand );
gboolean payee_hold_position_set_path ( GtkTreePath *path );
/* END_DECLARATION */
#endif
