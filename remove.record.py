import pandas as pd
import yaml
import os
import shutil
from datetime import datetime
import subprocess

excel_file_path = 'records.xlsx'
mkdocs_file_path = 'mkdocs.yml'
index_md_path = '.\\docs\\index.md'
docs_path = '.\\docs'

# Function to ensure directory exists
def ensure_dir(file_path):
    if not os.path.exists(file_path):
        os.makedirs(file_path)

# Update mkdocs.yml
with open(mkdocs_file_path, 'r') as file:
    mkdocs_data = yaml.safe_load(file)

# Reset ICPC and CodeForce training navs
mkdocs_data['nav'][1]['ICPC-Training'] = []
mkdocs_data['nav'][2]['CodeForce-Training'] = []

def process_row(row):
    folder_path = os.path.join(docs_path, row['category'], row['date'].strftime('%Y%m%d'))
    file_path = os.path.join(folder_path, 'training.md')
    
    # Update mkdocs.yml
    date_str = row['date'].strftime('%d/%m/%Y')
    rel_path = os.path.join(row['category'], row['date'].strftime('%Y%m%d'), 'training.md').replace('\\', '/')
    if row['category'].startswith('icpc'):
        mkdocs_data['nav'][1]['ICPC-Training'].append({date_str: rel_path})
    else:
        mkdocs_data['nav'][2]['CodeForce-Training'].append({date_str: rel_path})
    
    # Ensure the directory exists
    ensure_dir(folder_path)
    
    # Create or update the Markdown file if it doesn't exist
    if not os.path.exists(file_path):
        with open(file_path, 'w') as md_file:
            md_file.write(f"# {row['contest name']}\n\n")
            md_file.write(f"Virtual Contest: [{row['contest name']}]({row['contest link']})\n\n")
            md_file.write(f"Solutions: [{row['solution link']}]({row['solution link']})\n\n")
            md_file.write("# Submissions\n")

def main():
    # Load Excel data
    df = pd.read_excel(excel_file_path)

    # Ask the user for a category to remove
    categories = df['category'].unique()
    print("Select a category to remove a record from:")
    for index, category in enumerate(categories, 1):
        print(f"{index}. {category}")
    category_choice = int(input("Enter number: ")) - 1
    selected_category = categories[category_choice]

    # Filter data for selected category and ask for date
    category_data = df[df['category'] == selected_category]
    print(f"Available dates for {selected_category}:")
    for index, date in enumerate(category_data['date'], 1):
        print(f"{index}. {date}")
    date_choice = int(input("Enter number to select the date to remove: ")) - 1
    selected_date = category_data.iloc[date_choice]['date']

    # Remove entries from DataFrame
    df = df[~((df['category'] == selected_category) & (df['date'] == selected_date))]

    # Update the Excel file
    df.to_excel(excel_file_path, index=False)

    # Remove the directory and files
    selected_date_str = str(selected_date)  # Convert to string
    selected_date_datetime = datetime.strptime(selected_date_str, '%Y%m%d')  
    folder_path = os.path.join(docs_path, selected_category, selected_date_datetime.strftime('%Y%m%d'))
    if os.path.exists(folder_path):
        shutil.rmtree(folder_path)
    subprocess.run(['python', 'auto_record.py'])
if __name__ == "__main__":
    main()