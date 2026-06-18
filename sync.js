const fs = require("fs");

const NOTION_TOKEN = process.env.NOTION_TOKEN;
const DATABASE_ID = process.env.NOTION_DATABASE_ID;

const tagColors = {
  Add: "green_background",
  Refactor: "purple_background",
  Fix: "red_background",
  Polish: "pink_background",
  Update: "blue_background",
  Remove: "gray_background",
  Docs: "orange_background",
};

async function run() {
  try {
    const eventPath = process.env.GITHUB_EVENT_PATH;
    if (!eventPath) throw new Error("Not running inside GitHub Actions.");

    const eventData = JSON.parse(fs.readFileSync(eventPath, "utf8"));

    // We process in standard order [old, new] so the newest is inserted LAST.
    const commits = eventData.commits || [];

    if (commits.length === 0) {
      console.log("No commits found in this push.");
      return;
    }

    for (const commit of commits) {
      const rawMessage = commit.message;
      let tag = "Other";
      let cleanMessage = rawMessage;

      if (rawMessage.includes(":")) {
        const parts = rawMessage.split(":");
        let rawTag = parts[0].trim();
        tag = rawTag.charAt(0).toUpperCase() + rawTag.slice(1).toLowerCase();
        cleanMessage = parts.slice(1).join(":").trim();
      }

      const pillColor = tagColors[tag] || "default";

      const response = await fetch("https://api.notion.com/v1/pages", {
        method: "POST",
        headers: {
          Authorization: `Bearer ${NOTION_TOKEN}`,
          "Notion-Version": "2022-06-28",
          "Content-Type": "application/json",
        },
        body: JSON.stringify({
          parent: { database_id: DATABASE_ID },
          properties: {
            Message: { title: [{ text: { content: cleanMessage } }] },
            Tag: { select: { name: tag } },
            "Commit ID": {
              rich_text: [{ text: { content: commit.id.substring(0, 7) } }],
            },
            Author: {
              rich_text: [
                {
                  text: {
                    content:
                      commit.author.name || commit.author.username || "Unknown",
                  },
                },
              ],
            },
            Link: { url: commit.url },
          },
          children: [
            {
              object: "block",
              type: "heading_3",
              heading_3: {
                rich_text: [
                  { type: "text", text: { content: "Commit Details" } },
                ],
              },
            },
            {
              object: "block",
              type: "paragraph",
              paragraph: {
                rich_text: [
                  {
                    type: "text",
                    text: { content: ` ${tag} ` },
                    annotations: { bold: true, color: pillColor },
                  },
                  { type: "text", text: { content: `   ${cleanMessage}` } },
                ],
              },
            },
            { object: "block", type: "divider", divider: {} },
            {
              object: "block",
              type: "bulleted_list_item",
              bulleted_list_item: {
                rich_text: [
                  {
                    type: "text",
                    text: { content: "👤 Committer: " },
                    annotations: { bold: true, color: "gray" },
                  },
                  {
                    type: "text",
                    text: {
                      content:
                        commit.author.name ||
                        commit.author.username ||
                        "Unknown",
                    },
                  },
                ],
              },
            },
            {
              object: "block",
              type: "bulleted_list_item",
              bulleted_list_item: {
                rich_text: [
                  {
                    type: "text",
                    text: { content: "🔗 View on GitHub: " },
                    annotations: { bold: true, color: "gray" },
                  },
                  {
                    type: "text",
                    text: {
                      content: commit.id.substring(0, 7),
                      link: { url: commit.url },
                    },
                  },
                ],
              },
            },
          ],
        }),
      });

      if (!response.ok) {
        const errText = await response.text();
        throw new Error(`Notion API Error: ${errText}`);
      }

      console.log(`✅ Successfully synced: [${tag}] ${cleanMessage}`);
    }
  } catch (error) {
    console.error("❌ Sync Failed:", error.message);
    process.exit(1);
  }
}

run();
